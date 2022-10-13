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
               "or" "./trove  [-f trovefile]  [-b  ||  -r  ||  -u]  [-l length (positive integer)]  filelist");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    READ_FILE_STORAGE *fs = &read_file_storage;
    int opt;
    fs->file_name = strdup(default_file_name);
    max_word_length = 4;  
    bool bflag, rflag, uflag = false;
    
    int opterr = 0;
    while ((opt = getopt(argc, argv, OPTLIST)) != -1) {
        // Accept file name
        if (opt == 'f') {
            fs->file_name = strdup(optarg);
        }
        // Accept build option
        else if (opt == 'b') {
            bflag = true;
            if (rflag || uflag) {
                argc = -1;   
            }
        }
        // Accept remove option
        else if (opt == 'r') {
            rflag = true;
            if (bflag || uflag) {
                argc = -1;   
            }
        }
        // Accept update option
        else if (opt == 'u') {
            uflag = true;
            if (bflag || rflag) {
                argc = -1;   
            }
        }
        // Accept word length
        else if (opt == 'l') {
            max_word_length = atoi(optarg);
            if (max_word_length <= 0)
                argc = -1;
        }
        // Unknown argument
        else {
            argc = -1;
        }
    }
    if (argc <= 0) {
        usage(1);
    }
    while (optind < argc) {
        // If building a file
        if (bflag) {
            FILE *new_file_pointer = create_trove(fs->file_name);
            // Failed to open file
            if (new_file_pointer == NULL) {
                printf("Unable to open %s, please confirm it is correct", fs->file_name);
                perror(progname);
                exit(EXIT_FAILURE);
            }
            int file_type = file_attributes(argv[optind]);
            // file is directory
            if (file_type == 1) {
                list_directory(argv[optind]);
            }
            // file is reg file
            else if (file_type == 2) {
                add_file_path(&new_file_pointer, argv[optind]);
                read_file(argv[optind]);
            }
        }
        // If removing data from file
        else if (rflag) {
            FILE *remove_file_pointer = read_trove(fs->file_name);
        }
        // If updating a file
        else if (uflag) {
            FILE *update_file_pointer = read_trove(fs->file_name);
            
        }
        // If all flags are false
        else if (!bflag && !rflag && !uflag) {
            // If there are more than one word given
            if (optind++ < argc) {
                usage(1);
            }
            else {
                fs->word = argv[optind];
                FILE *find_pointer = read_trove(fs->file_name);
                find_names(&find_pointer);
            }
        }
    }
    return 1;
}
