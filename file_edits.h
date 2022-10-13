#ifndef FILE_EDITS_H
#define FILE_EDITS_H

extern void update_trove(char *file_name, int counter);
extern void remove_files(FILE *fp, int counter, char *to_be_removed_file);
extern void build_trove(FILE *build_pointer);

#endif
