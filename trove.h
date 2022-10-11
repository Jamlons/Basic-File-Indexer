#ifndef TROVE_H
#define TROVE_H

extern char *default_file_name;

extern void file_attributes(char *filename);
extern void read_file(char *filename);
extern void create_trove(char *trovename);

extern int max_word_length;

int default_word_length = 4;


struct file_storage {
    char *file_name;
    char *word;
};

struct file_storage *getstorage(void);
