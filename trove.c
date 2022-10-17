#include "trove.h"
#include "file_edits.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

char *progname;
#define OPTLIST "f:brul:"

void usage(bool flag) {
    if (flag) {
        printf("\nYou have entered the wrong invoking in the cmd.");
        printf("\nPlease make sure you are either using\n./trove  [-f trovefile]  word\nor\n./trove  [-f trovefile]  [-b  ||  -r  ||  -u]  [-l length (positive integer)]  filelist\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    int counter = 0;
    // Global structure
    READ_FILE_STRUCTURE *rfs = &read_file_structure;
    int opt;
    rfs->file_name = strdup(default_file_name);
    rfs->min_word_length = 4;  
    bool bflag = false;
    bool uflag = false;
    bool rflag = false;
    opterr = 0;
    printf("Gotten this far...\n");
    printf("\nArgument Count is: %d\n", argc);
    while ((opt = getopt(argc, argv, OPTLIST)) != -1) {
        printf("Searching for function\n");
        // Accept file name
        if (opt == 'f') {
            printf("Accepted file name option\n");
            rfs->file_name = strdup(optarg);
        }
        // Accept build option
        else if (opt == 'b') {
            printf("Accepted build option\n");
            bflag = true;
            if (rflag || uflag) {
                printf("\nAlready an option selected");
                if (rflag)
                    printf("\nrflag selected before");
                else
                    printf("\nuflag selected before");
                argc = -1;   
            }
        }
        // Accept remove option
        else if (opt == 'r') {
            printf("Accepted remove option\n");
            rflag = true;
            if (bflag || uflag) {
                printf("\nAlready an option selected");
                argc = -1;   
            }
        }
        // Accept update option
        else if (opt == 'u') {
            printf("Accepted update option\n");
            uflag = true;
            if (bflag || rflag) {
                printf("\nAlready an option selected");
                argc = -1;   
            }
        }
        // Accept word length
        else if (opt == 'l') {
            printf("Accepted length option\n");
            rfs->min_word_length = atoi(optarg);
            if (rfs->min_word_length <= 0) {
                argc = -1;
            }
        }
        // Unknown argument
        else {
            printf("Unknown argument\n");
            argc = -1;
        }
    }
    if (argc < 0) {
        printf("\nIncorrect Usage of Program");
        printf("\n%d", argc);
        usage(1);
    }
    // For each left over command
    while (optind < argc) {
        //If searching for a word
        if (!bflag && !rflag && !uflag) {
            int file_found = 0;
            printf("\nOptind count is: %d\n", optind);
            // If there are more than one word given
            int temp = optind;
            temp++;
            printf("Optind value is now: %d\n", optind);
            if (temp != argc) {
                usage(1);
            }
            else {
                printf("Grabbing word...\n");
                printf("Optind value is now: %d\n", optind);
                rfs->word = strdup(argv[optind]);
                printf("creating pointer");
                FILE *find_pointer = read_trove(rfs->file_name);
                file_found = find_names(find_pointer, rfs->word);
            }
            if (file_found) {
                exit(EXIT_SUCCESS);   
            }
            else
                exit(EXIT_FAILURE);
        }
        else if (bflag || rflag || uflag) {
            printf("Build | remove | update option selected\n");
            // Add each filename to a list called filelist
            FILE *test = read_trove(argv[optind]);
            if (test == NULL) {
                printf("Option %s is invalid. Please enter a filename\n", argv[optind]);
                exit(EXIT_FAILURE);
            }
            printf("Adding file to filelist\n");
            rfs->filelist[counter] = strdup(argv[optind]);
            counter++;
        }
        optind++;
    }
    // If building a file
        if (bflag) {
            printf("Building trove\n");
            build_trove(counter); //
        }
        // If removing data from file
        else if (rflag) {
            printf("removing trove\n");
            remove_files(rfs->file_name, counter, rfs->file_name);
        }
        // If updating a file
        else if (uflag) {
            printf("updating trove\n");
            update_trove(rfs->file_name, counter);
        }
    return 1;
}
