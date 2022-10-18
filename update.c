//FUNCTION FOR UPDATING GIVEN FILES INSIDE GIVEN TROVEFILE
// Most likely will not work, see findnames.c to see how it is done
#include "trove.h"
#include "file_edits.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

void update_trove(int counter) {
  // Global Structure
  READ_FILE_STRUCTURE *rfs = &read_file_structure;
  // Remove the files needing to be updated
  remove_files(counter);
  FILE *append_pointer = append_trove(file_name);
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
      list_directory(rfs->filelist[y]); 
    }
    else if (file_type == 1) {
      add_file_path(append_pointer, rfs->filelist[y]);
      read_file(append_pointer, rfs->filelist[y]);
    } 
  }
  fclose(append_pointer);
}

void build_trove(int counter) {
  printf("Building the trove now...\n");
  READ_FILE_STRUCTURE *rfs = &read_file_structure;
  FILE *build_pointer = create_trove(rfs->file_name);
  if (build_pointer == NULL) {
    printf("Unable to open %s, please make sure it is correct", rfs->file_name);
    perror(progname);
    exit(EXIT_FAILURE);
  }
  printf("\nCounter is %d\n", counter);
  for (int y = 0; y < counter; y++) {
    printf("Finding file type\n");
    int file_type = file_attributes(rfs->filelist[y]);
    // file is directory
    if (file_type == 2) {
      printf("File is a directory\n");
      list_directory(rfs->filelist[y]);
    }
    // file is reg file
    else if (file_type == 1) {
      printf("File is a reg file\n");
      printf("\nCurrent file name: %s", rfs->filelist[y]);
      add_file_path(build_pointer, rfs->filelist[y]);
      read_file(build_pointer, rfs->filelist[y]);
    }
  }
  fclose(build_pointer);
}
