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
               "or" "./trove  [-f trovefile]  [-b  |  -r  |  -u]  [-l length]  filelist");
        exit(EXIT_FAILURE);
    }
}

void main(int argc, char *argv[]) {
    struct file_storage *fs;
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
        else if (!bflag && !rflag && !uflag) {
            fs->word = strdup(optarg);
            // Search for word
            // If two words are given error out.
        }
        // If one command is given, this is the filelist
        else if (bflag || rflag || uflag) {
            //Loop to add each string to file list
            if (bflag) {
                FILE *build_pointer = create_trove(fs->file_name);
                add_file_info(build_pointer);
                // Add info to created trove file
                fclose(build_pointer);
            }
            else if (rflag) {
                FILE *remove_pointer = read_trove(fs->file_name);
                // 
                fclose(remove_pointer);
            // Remove info from trove file   
            }
            else if (uflag) {
              FILE *update_pointer = read_trove(fs->file_name);
                // Update info from trove file
            }
        }
        // Whoops unknown argument
        else {
            argc = -1;
        }
    }
    if (argc <= 0) {
        usage(1);
    }
}

