//FUNCTION TO REMOVE FILE INFO FROM GIVEN TROVEFILE
// WON'T WORK SEE findnames.c to see how its done
#include "trove.h"
#include "file_edits.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

//To remove lines from files - must duplicate the text file without said lines in it
void remove_files(int counter) {
  READ_FILE_STRUCTURE *rfs = &read_file_structure;
  char *temp_file_name = "as239gnma9yhq9109k23.txt";
  FILE *new_file = create_trove(temp_file_name);
  read_compressed();
  char full_path[PATH_MAX];
  sprintf(full_path, "%s.%s", rfs->file_name, "gz");
  // If file stream failed
  if (new_file == NULL) {
    printf("Unable to open %s, weird...", temp_file_name);
    perror(progname);
    exit(EXIT_FAILURE);
  }
  char *line = NULL;
  char *file_path = NULL;
  char *file_list_path = NULL;
  size_t linesize = 0;
  ssize_t linelen;
  int count = 1;
  // While grabbing each line of the text file
  while ((linelen = getline(&line, &linesize, stdin)) != -1) {
    int flag = 0;
    printf("Grabbing lines...\n");
    printf("Count is: %d\n", count);
    // If line is a file path (odd number)
    if ((count % 2) != 0) {
      // Save file path to a temp location
      file_path = strdup(line);
      // Make '\n' character null
      file_path[strlen(file_path) - 1] = 0;
      printf("File path is: %s\n", file_path);
      // For every file in filelist
      for (int a = 0; a < counter; a++) {
        file_list_path = get_resolved_path(rfs->filelist[a]);
        printf("Current file given is: %s\n", file_list_path);
        // If the file path and file list equal
        if (!strcmp(file_path, file_list_path)) {
          printf("Files match! Removing...\n");
          printf("File name is %s", line);
          // Increase count by two
          // This will skip over both the file path and the words in said file
          linelen = getline(&line, &linesize, stdin);
          printf("File contents is %s", line);
          // Why do we need this??? I can't figure out why it is needed for the remove function to work.
          flag = 1;
          continue;
        }
      }
      // If the file path is not to be removed add it to the new file
      if (flag)
        continue;
      printf("Adding %s to the file", file_path);
      fprintf(new_file, "%s\n", file_path);
      count++;
      continue;
    }
    // File path must be true - add all words to next line
    else {
      fprintf(new_file, "%s", line);
      count++;
    }
  }
  // Remove old file
  remove(rfs->file_name);
  remove(full_path);
  printf("Removing old file...\n");
  // Rename new file as old file name
  rename(temp_file_name, rfs->file_name);
  fclose(new_file);
  free(line);
}