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

// To return information regarding the usage of this program
void usage(bool flag) {
    if (flag) {
        printf("\nYou have entered the wrong invoking in the cmd.");
        printf("\nPlease make sure you are either using\n./trove  [-f trovefile]  word\nor\n./trove  [-f trovefile]  [-b  ||  -r  ||  -u]  [-l length (positive integer)]  filelist\n");
        exit(EXIT_FAILURE);
    }
}
// Main function of trove
int main(int argc, char *argv[]) {
    int counter = 0;
    // Global structure
    READ_FILE_STRUCTURE *rfs = &read_file_structure;
    int opt;
    // Default the structures with global variables
    rfs->file_name = strdup(default_file_name);
    rfs->min_word_length = 4;  
    bool bflag = false;
    bool uflag = false;
    bool rflag = false;
    opterr = 0;
    while ((opt = getopt(argc, argv, OPTLIST)) != -1) {
        // Accept file name
        if (opt == 'f') {
            rfs->file_name = strdup(optarg);
        }
        // Accept build option
        else if (opt == 'b') {
            bflag = true;
            // If another option has already been given.
            if (rflag || uflag) {
                argc = -1;   
            }
        }
        // Accept remove option
        else if (opt == 'r') {
            rflag = true;
            // If another option has already been given.
            if (bflag || uflag) {
                argc = -1;   
            }
        }
        // Accept update option
        else if (opt == 'u') {
            uflag = true;
            // If another option has already been given.
            if (bflag || rflag) {
                argc = -1;   
            }
        }
        // Accept word length
        else if (opt == 'l') {
            rfs->min_word_length = atoi(optarg);
            // If word length isn't positive or is 0
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
        usage(1);
    }
    // For each left over command
    while (optind < argc) {
        //If searching for a word
        if (!bflag && !rflag && !uflag) {
            int file_found = 0;
            int temp = optind;
            temp++;
            // If there are more than one word given break
            if (temp != argc) {
                usage(1);
            }
            else {
                // Add word to global structure
                rfs->word = strdup(argv[optind]);
                // Create pointer in read+ mode
                FILE *find_pointer = read_trove(rfs->file_name);
                if (find_pointer == NULL) {
                    exit(EXIT_FAILURE);
                }
                // Find the words within given file
                file_found = find_names(find_pointer);
            }
            if (file_found) {
                exit(EXIT_SUCCESS);   
            }
            else
                exit(EXIT_FAILURE);
        }
        else if (bflag || rflag || uflag) {
            // For each file given add to a list
            rfs->filelist[counter] = strdup(argv[optind]);
            counter++;
        }
        optind++;
    }
        // If building a file
        if (bflag) {
            build_trove(counter); 
        }
        // If removing data from file
        else if (rflag) {
            remove_files(rfs->file_name, counter, rfs->file_name);
        }
        // If updating a file
        else if (uflag) {
            update_trove(rfs->file_name, counter);
        }
    return 1;
}
