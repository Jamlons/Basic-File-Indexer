#ifndef TROVE_H
#define TROVE_H

#define BUFSIZE = 100000;
extern char *default_file_name;

extern int file_attributes(char *filename);
extern void read_file(char *filename);
extern FILE *create_trove(char *trovename);
extern FILE *append_trove(char *filename);
extern FILE *read_trove(char *filename);
extern void add_file_path(FILE *fp, char *file_name);
extern void find_names(FILE *fp);

extern int min_word_length;
extern char *filelist[];

typedef struct{
    char *file_name;
    char *word;
}READ_FILE_STRUCTURE;

