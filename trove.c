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
    while ((opt = getopt(argc, argv, OPTLIST)) != -1) {
        if (opt == 'f') {
            fs->file_name = strdup(optarg);
        }
        else if (opt == 'b') {
            create_file(fs->file_name);
            // Add info from file list to created file
        }
        else if (opt == 'r') {
            //Remove file info from trove_file
        }
        else if (opt == 'u') {
            // Update info from trove_file
        }
        else if (opt == 'l') {
            // Grab word length
        }
    }
    for (; optind < argc;
}
