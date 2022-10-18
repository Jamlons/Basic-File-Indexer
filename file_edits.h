// Header File to allow main() to access functions to edit, update and remove information from trove files.
#ifndef FILE_EDITS_H
#define FILE_EDITS_H

extern void update_trove(char *file_name, int counter);
extern void remove_files(char * filename, int counter, char *to_be_removed_file);
extern void build_trove(int counter);

#endif
