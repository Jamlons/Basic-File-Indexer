#include "trove.h"
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
        printf("\n%s" "You have entered the wrong invoking in the cmd.");
        printf("\n%s\n%s\n%s" "Please make sure you are either using" "./trove  [-f trovefile]  word"
               or "./trove  [-f trovefile]  [-b  |  -r  |  -u]  [-l length]  filelist");
        main();
    }
}

void main(int argc, char *argv[]) {
    struct file_storage *fs;
    int opt;
    fs->file_name = strdup(default_file_name);
    max_word_length = 4;
    
    bool bflag = false;
    bool rflag = false;
    bool uflag = false;
    
    opterr = 0;
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
            max_word_length = atoi(optarg);
        }
        // If no commands are given, this is the word.
        else if (bflag || rflag || uflag) {
            fs->word = strdup(optarg);
        }
        // If one command is given, this is the filelist
        else if (bflag || rflag || uflag){
            //Loop to add each string to file list
        }
        // Whoops from argument
        else {
            argc = -1;
        }
    }
    if (argc <= 0) {
        usage(1);
    }
    // Run all code here
}

