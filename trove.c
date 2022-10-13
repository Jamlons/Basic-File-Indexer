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
        printf("\n%s" "You have entered the wrong invoking in the cmd.");
        printf("\n%s\n%s\n%s" "Please make sure you are either using" "./trove  [-f trovefile]  word"
               "or" "./trove  [-f trovefile]  [-b  ||  -r  ||  -u]  [-l length (positive integer)]  filelist");
        exit(EXIT_FAILURE);
    }
}

void build_trove(FILE *build_pointer) {
    int file_type = file_attributes(filelist[y]);
    // file is directory
    if (file_type == 1) {
        list_directory(filelist[y]);
    }
    // file is reg file
    else if (file_type == 2) {
        add_file_path(build_pointer, filelist[y]);
        read_file(filelist[y]);
    }
}

int main(int argc, char *argv[]) {
    int counter = 0;
    READ_FILE_STORAGE read_file_storage;
    int opt;
    read_file_storage.file_name = strdup(default_file_name);
    max_word_length = 4;  
    bool bflag, rflag, uflag = false;
    
    int opterr = 0;
    while ((opt = getopt(argc, argv, OPTLIST)) != -1) {
        // Accept file name
        if (opt == 'f') {
            read_file_storage.file_name = strdup(optarg);
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
        if (bflag || rflag || uflag) {
            // Add each filename to a list called filelist
            filelist[counter] = strdup(argv[optind]);
            counter++;
        }
        else if (!bflag && !rflag && !uflag) {
            int file_found = 0;
            // If there are more than one word given
            if (optind++ < argc) {
                usage(1);
            }
            else {
                read_file_storage.word = argv[optind];
                FILE *find_pointer = read_trove(read_file_storage.file_name);
                file_found = find_names(find_pointer);
            }
            if (file_found) {
                exit(EXIT_SUCCESS);   
            }
            else
                exit(EXIT_FAILURE);
        }
    }
    // If building a file
        if (bflag) {
            for (int y = 0; y < counter; y++) {
                FILE *new_file_pointer = create_trove(read_file_storage.file_name);
                // Failed to open file
                if (new_file_pointer == NULL) {
                    printf("Unable to open %s, please confirm it is correct", read_file_storage.file_name);
                    perror(progname);
                    exit(EXIT_FAILURE);
                }
                build_trove(new_file_pointer);
            }
            fclose(new_file_pointer);
        }
        // If removing data from file
        else if (rflag) {
            remove_files(read_file_storage.file_name, counter, read_file_storage.file_name);
        }
        // If updating a file
        else if (uflag) {
            update_trove(read_file_storage.file_name, counter);
        }
    return 1;
}
