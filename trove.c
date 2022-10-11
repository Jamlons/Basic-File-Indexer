#include "trove.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

char *progname;
#define OPTLIST "f:brul:"

main(int argc, char *argv[]) {
    struct file_storage *fs;
    int opt;
    char *filename = NULL;
    int value = DEFAULT_VALUE;
    fs->file_name = strdup(default_file_name);
    
    opterr = 0;
    bool bflag = false;
    bool rflag = false;
    bool uflag = false;
    while ((opt = getopt(argc, argv, OPTLIST)) != -1) {
        // Accept file name
        if (opt == 'f') {
            fs->file_name = strdup(optarg);
        }
        // Accept build option
        else if (opt == 'b') {
            bflag = true;
        }
        // Accept remove option
        else if (opt == 'r') {
            rflag = true;
        }
        // Accept update option
        else if (opt == 'u') {
            uflag = true;
        }
        // Accept word length
        else if (opt == 'l') {
            // Grab word length
            word_length = atoi(optarg);
        }
        // If no build, update or remove option selected - search for word.
        else if (bflag && rflag && uflag) {
            fs-> word = strdup(optarg);
            // Search for this word.
        }
        else {
            // Add filelist info to file
        }
    }
}

