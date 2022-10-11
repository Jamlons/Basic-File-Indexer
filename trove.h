#ifndef TROVE_H
#define TROVE_H

extern char *default_file_name;

extern void file_attributes(char *filename);
extern void read_file(char *filename);

extern int max_word_length;


struct file_storage {
    char *file_name;
    char *word;
};
