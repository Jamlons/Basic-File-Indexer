//FUNCTION FOR UPDATING GIVEN FILES INSIDE GIVEN TROVEFILE
#include "trove.h"

void update_trove(char *file_name, int counter) {
  FILE *update_file_pointer = read_trove(file_name);
  if (update_file_pointer = NULL) {
    printf("Unable to open %s, please confirm it is correct", read_file_storage.file_name);
    perror(progname);
    exit(EXIT_FAILURE);
  }
  remove_files(update_file_pointer, counter, file_name);
  for (int y = 0; y < counter; y ++) {
    build_trove(update_file_pointer); 
  }
}
