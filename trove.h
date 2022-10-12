#ifndef TROVE_H
#define TROVE_H

extern char *default_file_name;

extern void file_attributes(char *filename);
extern void read_file(char *filename);
extern void create_trove(char *trovename);

extern int min_word_length;

typedef struct {
    char *file_name;
    char *word;
}file_structure;

extern file_structure globalStruct;
