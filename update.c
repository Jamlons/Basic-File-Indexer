//FUNCTION FOR UPDATING GIVEN FILES INSIDE GIVEN TROVEFILE
// Most likely will not work, see findnames.c to see how it is done
#include "trove.h"
#include "file_edits.h"
#include <stdlib.h>
#include <unistd.h>
// Function to add filelist info the end of trovefile
void update_trove(int counter) {
  // Global Structure
  READ_FILE_STRUCTURE *rfs = &read_file_structure;
  // Remove the files needing to be updated
  remove_files(counter);
  FILE *append_pointer = append_trove(rfs->file_name);
  // If appending pointer is empty
  if (append_pointer == NULL) {
    printf("Unable to open %s, please make sure it is correct\n", rfs->file_name);
    perror(progname);
    exit(EXIT_FAILURE);
  }
  // For every file within filelist
  for (int y = 0; y < counter; y++) {
    int file_type = file_attributes(rfs->filelist[y]);
    if (file_type == 2) {
      list_directory(rfs->filelist[y], append_pointer); 
    }
    else if (file_type == 1) {
      add_file_path(append_pointer, rfs->filelist[y]);
      read_file(append_pointer, rfs->filelist[y]);
    } 
  }
  fclose(append_pointer);
}
// Function to build the trovefile
void build_trove(int counter) {
  READ_FILE_STRUCTURE *rfs = &read_file_structure;
  FILE *build_pointer = create_trove(rfs->file_name);
  if (build_pointer == NULL) {
    printf("Unable to open %s, please make sure it is correct", rfs->file_name);
    perror(progname);
    exit(EXIT_FAILURE);
  }
  for (int y = 0; y < counter; y++) {
    int file_type = file_attributes(rfs->filelist[y]);
    // file is directory
    if (file_type == 2) {
      list_directory(rfs->filelist[y], build_pointer);
    }
    // file is reg file
    else if (file_type == 1) {
      add_file_path(build_pointer, rfs->filelist[y]);
      read_file(build_pointer, rfs->filelist[y]);
    }
  }
  fclose(build_pointer);
}
