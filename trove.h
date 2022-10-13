#ifndef TROVE_H
#define TROVE_H

#define BUFSIZE = 100000;
extern char *default_file_name;

extern void file_attributes(char *filename);
extern void read_file(char *filename);
extern FILE *create_trove(char *trovename);
extern FILE *append_trove(char *filename);
extern FILE *read_trove(char *filename);

extern int min_word_length;

typedef struct {
    char *file_name;
    char *word;
}READ_FILE_STRUCTURE;

READ_FILE_STRUCTURE read_file_storage;
