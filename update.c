//FUNCTION FOR UPDATING GIVEN FILES INSIDE GIVEN TROVEFILE
#include "trove.h"
#include "file_edits.h"

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

void build_trove(char *filename) {
    FILE *build_pointer = create_trove(filename);
    if (build_pointer == NULL) {
      printf("Unable to open %s, please make sure it is correct", filename);
      perror(progname);
      exit(EXIT_FAILURE);
    }
    int file_type = file_attributes(filelist[y]);
    // file is directory
    if (file_type == 1) {
        list_directory(filelist[y]);
    }
    // file is reg file
    else if (file_type == 2) {
        add_file_path(build_pointer, filelist[y]);
        read_file(filelist[y]);
    }
  fclose(build_pointer);
}
