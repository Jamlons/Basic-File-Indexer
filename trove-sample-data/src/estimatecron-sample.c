#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include <ctype.h>
#include <time.h>

//  written by Chris.McDonald@uwa.edu.au, Aug 2022
//  under licence - creativecommons.org/licenses/by-nc-sa/4.0/

//  compile with:
//      cc -std=c11 -Wall -Werror -o estimatecron estimatecron.c

//  execute with:
//      ./estimatecron month crontab-file estimates-file
//  or:
//      DEBUG=y ./estimatecron month crontab-file estimates-file

#define MAX_LINE_LENGTH         100
#define MAX_COMMAND_LENGTH       40

#define MAX_CRONTABS             20
#define MAX_ESTIMATES            20
#define MAX_PROCESSES            20

#define COLUMNS_CRONTAB           6
#define COLUMNS_ESTIMATES         2

#define CHAR_COMMENT            '#'
#define STR_ASTERISK            "*"
#define ASTERISK                (-1)

//  DATA READ FROM crontab-file PROVIDED ON COMMAND-LINE
//  THE FIELDS ARE NAMED TO MATCH THOSE OF A struct tm FROM <time.h>
struct {
    int     min;                    // 0..59, or ASTERISK iff '*'
    int     hour;                   // 0..23, ...
    int     mday;                   // 1..31, ...
    int     mon;                    // 0..11, ...
    int     wday;                   // 0..6,  ...
    int     cmdindex;               // index into the estimates[]
} crontabs[MAX_CRONTABS];

int n_crontabs   = 0;

//  DATA READ FROM estimates-file PROVIDED ON COMMAND-LINE
struct {
    char    name[MAX_COMMAND_LENGTH+1];     // +1 for '\0' byte
    int     minutes;                // estimate of execution time
    int     ntimes;                 // number of times invoked
} estimates[MAX_ESTIMATES];

int n_estimates = 0;

//  THE VERY SIMPLE 'PROCESS TABLE' REPRESENTING CURRENTLY-RUNNING PROCESSES
struct {
    int     pid;                    // 1, 2, ...
    int     cmdindex;               // index into the estimates[]
    int     finishtime;             // in minutes
} process_table[MAX_PROCESSES];

int n_processes         = 0;

//  REQUIRED STATISTICS
int total_invoked       = 0;        // total commands ever invoked
int max_running         = 0;        // max processes running at any time

bool debug              = false;    // true iff environ. variable DEBUG defined

//  ------------------------------------------------------------------

#define N_MONTHS    12

int days_in_month[N_MONTHS] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

char *month_names[N_MONTHS] = {
    "jan", "feb", "mar", "apr", "may", "jun",
    "jul", "aug", "sep", "oct", "nov", "dec"
};

#define N_WEEKDAYS    7

char *weekday_names[N_WEEKDAYS] = {
    "sun", "mon", "tue", "wed", "thu", "fri", "sat"
};

//  ------------------------------------------------------------------

//  REMOVE ANY TRAILING end-of-line CHARACTERS FROM THE LINE (from Lecture-8)
void trim_line(char line[])
{
//  LOOP UNTIL WE REACH THE END OF line
    int i = 0;
    while(line[i] != '\0') {
        if( line[i] == '\r' || line[i] == '\n' ) { //  carriage-return or newline?
            line[i] = '\0'; // overwrite with null-byte
            break;          // leave the loop early
        }
        i = i+1;            // iterate through character array
    }
}

//  is_whitespace() COULD BE IMPLEMENTED AS A PREPROCESSOR MACRO OR A C FUNCTION
#define is_whitespace(ch)   (ch == ' ' || ch == '\t')

bool is_comment_line(char line[])
{
    int i = 0;
    while(is_whitespace(line[i])) {     // skip until first non-whitespace
        ++i;
    }
    return (line[i] == CHAR_COMMENT);
}

//  ------------------------------------------------------------------

bool all_digits(char str[])
{
    for(int i=0 ; str[i] != '\0' ; ++i) {
        if(!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

int check_integer(char str[], int minvalue, int maxvalue, char errdesc[])
{
    if(strcmp(str, STR_ASTERISK) == 0) {
        return ASTERISK;
    }
    else if(all_digits(str)) {
        int value   = atoi(str);
        if(value >= minvalue && value <= maxvalue) {
            return value;
        }
    }
    fprintf(stderr, "'%s' is an invalid %s\n", str, errdesc);
    exit(EXIT_FAILURE);
}

int check_month(char str[], bool permit_asterisk)
{
    if(permit_asterisk && strcmp(str, STR_ASTERISK) == 0) {
        return ASTERISK;
    }
    else if(all_digits(str)) {
        int month   = atoi(str);
        if(month >= 0 && month < N_MONTHS) {
            return month;
        }
    }
    else {
        for(int m=0 ; m<N_MONTHS ; ++m) {
            if(strncmp(month_names[m],str,3) == 0 && str[3] == '\0') {
                return m;
            }
        }
    }
    fprintf(stderr, "'%s' is an invalid month\n", str);
    exit(EXIT_FAILURE);
}

int check_weekday(char str[])
{
    if(strcmp(str, STR_ASTERISK) == 0) {
        return ASTERISK;
    }
    else if(all_digits(str)) {
        int weekday   = atoi(str);
        if(weekday >= 0 && weekday < N_WEEKDAYS) {
            return weekday;
        }
    }
    else {
        for(int m=0 ; m<N_WEEKDAYS ; ++m) {
            if(strncmp(weekday_names[m],str,3) == 0 && str[3] == '\0') {
                return m;
            }
        }
    }
    fprintf(stderr, "'%s' is an invalid day of the week\n", str);
    exit(EXIT_FAILURE);
}

int find_command_in_estimates(char command[])
{
    for(int e=0 ; e<n_estimates ; ++e) {
        if(strcmp(estimates[e].name, command) == 0) {
            return e;
        }
    }
    fprintf(stderr, "'%s' is an unknown command\n", command);
    exit(EXIT_FAILURE);
}

//  ------------------------------------------------------------------

void print_integer(int x)
{
    if(x == ASTERISK) {
        printf(" %s ", STR_ASTERISK);
    }
    else {
        printf("%2i ", x);
    }
}

void print_1_crontab_entry(int c)
{
    print_integer(crontabs[c].min);
    print_integer(crontabs[c].hour);
    print_integer(crontabs[c].mday);
    print_integer(crontabs[c].mon);
    print_integer(crontabs[c].wday);
    printf("\t\t%s\n", estimates[crontabs[c].cmdindex].name);
}

//  (NOT-REQUIRED)  PRINT THE CONTENTS OF crontabs[] TO CONFIRM WHAT WAS READ
void display_crontabs(void)
{
    if(debug && n_crontabs > 0) {
        printf("crontab entries:\n");
        for(int c=0 ; c<n_crontabs ; ++c) {
            printf("\t");
            print_1_crontab_entry(c);
        }
        printf("\n");
    }
}

//  (NOT-REQUIRED)  PRINT THE CONTENTS OF estimates[] TO CONFIRM WHAT WAS READ
void display_estimates(void)
{
    if(debug && n_estimates > 0) {
        printf("estimates entries:\n");
        for(int e=0 ; e<n_estimates ; ++e) {
            printf("\t%-40s\t%i\n", estimates[e].name, estimates[e].minutes);
        }
        printf("\n");
    }
}

//  ------------------------------------------------------------------

void read_crontab_file(char filename[])
{
    FILE *fp    = fopen(filename, "r");

//  REPORT AN ERROR, TERMINATE, IF FILE CANNOT BE OPENED
    if(fp == NULL) {
        fprintf(stderr, "unable to open crontab-file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    int lc  = 0;                                // linecount (for error reports)
    char    line[MAX_LINE_LENGTH+1];
    while(fgets(line, sizeof(line), fp) != NULL) {
        ++lc;
        trim_line(line);                        // remove \n or \r

//  IGNORE A COMMENT LINE?
        if(is_comment_line(line)) {
            continue;
        }

//  EXPECTED FORMAT:    mins hours monthday month weekday    command-name
        char min [MAX_LINE_LENGTH];     // probably longer than needed,
        char hour[MAX_LINE_LENGTH];     // ... but guaranteed to be long enough
        char mday[MAX_LINE_LENGTH];
        char mon [MAX_LINE_LENGTH];
        char wday[MAX_LINE_LENGTH];
        char cmd [MAX_LINE_LENGTH];
        int  valid_columns  = 0;

        if(sscanf(line, "%s %s %s %s %s %s", min, hour, mday, mon, wday, cmd) == COLUMNS_CRONTAB) {
            crontabs[n_crontabs].min       = check_integer(min,  0, 59, "minute");
            crontabs[n_crontabs].hour      = check_integer(hour, 0, 23, "hour");
            crontabs[n_crontabs].mday      = check_integer(mday, 1, 31, "day of the month");
            crontabs[n_crontabs].mon       = check_month(mon,    true);
            crontabs[n_crontabs].wday      = check_weekday(wday);
            crontabs[n_crontabs].cmdindex  = find_command_in_estimates(cmd);

            if(crontabs[n_crontabs].mon == ASTERISK ||
                crontabs[n_crontabs].mday <= days_in_month[crontabs[n_crontabs].mon]) {
                valid_columns               = COLUMNS_CRONTAB;
            }
        }
        if(valid_columns != COLUMNS_CRONTAB) {
            fprintf(stderr, "line %i unrecognized in crontab-file: '%s'\n", lc, line);
            exit(EXIT_FAILURE);
        }
        ++n_crontabs;
    }                           // end of fgets(....
    fclose(fp);
}

//  ------------------------------------------------------------------

void read_estimates_file(char filename[])
{
    FILE *fp    = fopen(filename, "r");

//  REPORT AN ERROR, TERMINATE, IF FILE CANNOT BE OPENED
    if(fp == NULL) {
        fprintf(stderr, "unable to open estimates-file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    int lc  = 0;                                // linecount (for error reports)
    char    line[MAX_LINE_LENGTH+1];
    while(fgets(line, sizeof(line), fp) != NULL) {
        ++lc;
        trim_line(line);                        // remove \n or \r

//  IGNORE A COMMENT LINE?
        if(is_comment_line(line)) {
            continue;
        }

//  EXPECTED FORMAT:    command-name   minutes
        int valid_columns = 0;
        char    minutes[MAX_LINE_LENGTH];

        if(sscanf(line, "%s %s", estimates[n_estimates].name, minutes) == COLUMNS_ESTIMATES) {
            estimates[n_estimates].minutes  = atoi(minutes);
            if(estimates[n_estimates].minutes > 0) {
                valid_columns   = COLUMNS_ESTIMATES;
            }
        }
        if(valid_columns != COLUMNS_ESTIMATES) {
            fprintf(stderr, "line %i unrecognized in estimates-file: '%s'\n", lc, line);
            exit(EXIT_FAILURE);
        }
        ++n_estimates;
    }                           // end of fgets(....
    fclose(fp);
}

//  ------------------------------------------------------------------

//  'EXECUTE' A NEW COMMAND BY ADDING IT TO THE PROCESS TABLE, UPDATING STATISTICS
void invoke_process(int c, int now, char when[])
{
    if(n_processes < MAX_PROCESSES) {
        static int  pid  = 0;                   // not required, just for debugging

        int cmdindex = crontabs[c].cmdindex;

//  ADD THIS NEW PROCESS TO THE PROCESS TABLE
        process_table[n_processes].cmdindex      = cmdindex;
        process_table[n_processes].pid           = ++pid;
        process_table[n_processes].finishtime    = now + estimates[cmdindex].minutes;
        ++n_processes;

        ++total_invoked;
        ++estimates[cmdindex].ntimes;

//  HAVE WE FOUND A NEW MAXIMUM NUMBER OF EVER-RUNNING PROCESSES?
        if(max_running < n_processes) {
            max_running = n_processes;
        }

        if(debug) {
            if(when[0]) {
                printf("%s\n", when);
                when[0] = '\0';
            }
            printf("\t\tinvoke (pid=%i, nrunning=%i)\t", pid, n_processes);
            print_1_crontab_entry(c);
        }
    }
    else if(debug) {
        printf("\t\tcannot invoke new process, maximum=%i\n", MAX_PROCESSES);
    }
}

//  HAVE ANY OF THE CURRENTLY RUNNING PROCESSES NOW FINISHED?
void terminate_processes(int now, char when[])
{
    for(int p=0 ; p<n_processes ; ++p) {
        if(process_table[p].finishtime <= now) {            // finished!

            if(debug) {
                if(when[0]) {
                    printf("%s\n", when);
                    when[0] = '\0';
                }
                printf("\t\thas-terminated (pid=%i, nrunning=%i)\t%s\n",
                        process_table[p].pid,
                        n_processes-1,
                        estimates[ process_table[p].cmdindex].name);
            }
//  REMOVE THIS TERMINATED PROCESS FROM PROCESS TABLE
            process_table[p] = process_table[n_processes-1];
            --n_processes;
            --p;
        }
    }
}

//  ------------------------------------------------------------------

//  a_match() COULD BE IMPLEMENTED AS A PREPROCESSOR MACRO OR A C FUNCTION
#define a_match(x, y)   (x == y || x == ASTERISK)

//  DATE/CALENDAR BASED CODE RE-USED FROM Workshop-2
void simulate(int this_minute, struct tm *tp)
{
    char when[40];

    if(debug) {
        sprintf(when, "@%02i:%02i\t%02i/%s",
            tp->tm_hour, tp->tm_min, tp->tm_mday, month_names[tp->tm_mon]);
    }

//  REMOVE ANY PROCESSES THAT HAVE TERMINATED WITHIN THE PAST MINUTE
    terminate_processes(this_minute, when);

//  ITERATE OVER ALL CRONTAB ENTRIES, FINDING MATCHING ONES
    for(int c=0 ; c<n_crontabs ; ++c) {

//  DOES THE CURRENT TIME MATCH ALL OF THE DATE/TIME FIELDS?
        if(a_match(crontabs[c].min,     tp->tm_min)     &&
           a_match(crontabs[c].hour,    tp->tm_hour)    &&
           a_match(crontabs[c].mday,    tp->tm_mday)    &&
           a_match(crontabs[c].mon,     tp->tm_mon)     &&
           a_match(crontabs[c].wday,    tp->tm_wday))   {

//  IF HERE, THEN THIS CRONTAB ENTRY REQUIRES A NEW PROCESS TO BE INVOKED
                invoke_process(c, this_minute, when);
        }
    }                           // foreach crontab entry
}

//  ------------------------------------------------------------------

//  DATE/CALENDAR BASED CODE RE-USED FROM Workshop-2
void iterate_over_all_minutes_v1(int month, int year)
{
//  SET ALL FIELDS OF tm TO ZERO TO MAKE SOME FIELDS 'UNKNOWN'
    struct tm tm;
    memset(&tm, 0, sizeof(tm));

//  INITIALIZE THE FILEDS THAT WE ALREADY KNOW
    tm.tm_mday      = 1;                    // 1st day of required month
    tm.tm_mon       = month;                // 0=jan, 1=feb, ....
    tm.tm_year      = year - 1900;

    time_t  secs;
    int     mins;

//  ITERATE OVER ALL OF THE MINUTES IN THE REQUIRED MONTH
    int total_minutes    = 60 * 24 * days_in_month[month];
    for(secs=mktime(&tm), mins=0 ; mins < total_minutes ; secs += 60, ++mins) {
        struct tm *tp   = localtime(&secs);

        simulate(mins, tp);
    }
    if(debug) {
        printf("\n");
    }
}

void iterate_over_all_minutes_v2(int month, int year)
{
//  SET ALL FIELDS OF tm TO ZERO TO MAKE SOME FIELDS 'UNKNOWN'
    struct tm tm;
    memset(&tm, 0, sizeof(tm));

//  INITIALIZE THE FILEDS THAT WE ALREADY KNOW
    tm.tm_mday      = 1;                    // 1st day of required month
    tm.tm_mon       = month;                // 0=jan, 1=feb, ....
    tm.tm_year      = year - 1900;

//  ASK THE POSIX FUNCTION mktime TO DETERMINE THE 'UNKNOWN' FIELDS
//  See: http://pubs.opengroup.org/onlinepubs/9699919799/
    mktime(&tm);

    tm.tm_mday      = 0;
    tm.tm_wday      = (tm.tm_wday + 6) % 7; // previous day-of-the-week

//  ITERATE OVER ALL OF THE MINUTES IN THE REQUIRED MONTH
    int total_minutes    = 60 * 24 * days_in_month[month];
    for(int mins=0 ; mins < total_minutes ; ++mins) {

        tm.tm_min   = mins % 60;
        tm.tm_hour  = (mins / 60) % 24;

        if(tm.tm_hour == 0 && tm.tm_min == 0) { // now at midnight, 00:00
            ++tm.tm_mday;                       // advance to tomorrow
            tm.tm_wday = (tm.tm_wday + 1) % 7;
        }
        simulate(mins, &tm);
    }
    if(debug) {
        printf("\n");
    }
}

//  ------------------------------------------------------------------

void reset_statistics(void)
{
    n_processes     = 0;
    total_invoked   = 0;
    max_running     = 0;
}

void print_statistics(void)
{
    if(debug && n_estimates > 0) {
        printf("command invocations:\n");
        for(int e=0 ; e<n_estimates ; ++e) {
            printf("\t%-40s\t%i\n", estimates[e].name, estimates[e].ntimes);
        }
        printf("\n");
    }

    int maxi    = -1;               // maximum invoked
    int maxe    = -1;               // index in estimates[] of maximum

    for(int e=0 ; e<n_estimates ; ++e) {
        if(maxi < estimates[e].ntimes) {
            maxi    = estimates[e].ntimes;
            maxe    = e;
        }
    }
//  THE ALL-IMPORTANT FINAL 'RESULT' LINE
    printf("%s\t%i\t%i\n",
        (maxe == -1) ? "<none>" : estimates[maxe].name, total_invoked, max_running );
}

//  ------------------------------------------------------------------

int main(int argc, char *argv[])
{
    if(argc != 4) {
        fprintf(stderr, "Usage: %s month crontab-file estimates-file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    debug   = (getenv("DEBUG") != NULL);    // not required for project

//  READ THE estimates-file FIRST SO THAT ALL COMMAND-NAMES ARE KNOWN
    read_estimates_file(argv[3]);
//  (NOT-REQUIRED)  PRINT THE CONTENTS OF estimates[] TO CONFIRM WHAT WAS READ
    display_estimates();

//  READ THE crontab-file, ONLY ACCEPTING KNOWN COMMAND NAMES
    read_crontab_file  (argv[2]);
//  (NOT-REQUIRED)  PRINT THE CONTENTS OF crontabs[] TO CONFIRM WHAT WAS READ
    display_crontabs();

    if(n_crontabs > 0) {
//  MONTH MAY BE REQUESTED WITH AN INTEGER (0..11) OR 3-LETTER NAME, NOT '*'
        int     month   = check_month(argv[1], false);

        time_t  now     = time(NULL);
        int     year    = localtime(&now)->tm_year+1900;   // current year

        reset_statistics();
            iterate_over_all_minutes_v1(month, year);
        print_statistics();

        reset_statistics();
            iterate_over_all_minutes_v2(month, year);
        print_statistics();
    }
    exit(EXIT_SUCCESS);
    return 0;
}
