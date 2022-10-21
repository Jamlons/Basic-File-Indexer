#ifndef TROVE_H
#include <stdio.h>
#define TROVE_H

#define BUFSIZE 100000
extern char *default_file_name;
extern int EXIT_FAILURE;
extern int EXIT_SUCCESS;

extern int file_attributes(char *filename);
extern void read_file(FILE *fp, char *filename);
extern FILE *create_trove(char *trovename);
extern FILE *append_trove(char *filename);
extern FILE *read_trove(char *filename);
extern void add_file_path(FILE *fp, char *file_name);
extern void list_directory(char *dirname, FILE *fp);
extern int find_names(FILE *fp);
extern char *get_resolved_path(char *file_name);

extern char * progname;

typedef struct{
    char *file_name;
    char *word;
    int min_word_length;
    char *resolved_path;
    char * filelist[];
}READ_FILE_STRUCTURE;

typedef struct{
    int dircounter;
    char * dirlist[];
}DIRECTORY_STRUCTURE;

READ_FILE_STRUCTURE read_file_structure;
DIRECTORY_STRUCTURE dir_struct;

#endif