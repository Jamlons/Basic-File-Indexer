//FUNCTION TO REMOVE FILE INFO FROM GIVEN TROVEFILE
// WON'T WORK SEE findnames.c to see how its done
#include "trove.h"
#include "file_edits.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//To remove lines from files - must duplicate the text file without said lines in it
void remove_files(int counter) {
  READ_FILE_STRUCTURE *rfs = &read_file_structure;
  char *temp_file_name = "as239gnma9yhq9109k23.txt";
  FILE *new_file = create_trove(temp_file_name);
  FILE *old_file = read_trove(rfs->file_name);
  // If file stream failed
  if (new_file == NULL) {
    printf("Unable to open %s, weird...", temp_file_name);
    perror(progname);
    exit(EXIT_FAILURE);
  }
  // If file stream failed
  if (old_file == NULL) {
    printf("Unable to open %s, please make sure it is correct", old_file_name);
    perror(progname);
    exit(EXIT_FAILURE);
  }
  char *buf;
  char *line = NULL;
  char *file_path = NULL;
  size_t linesize = 0;
  ssize_t linelen;
  int count = 1;
  // While grabbing each line of the text file
  while ((linelen = getline(&line, &linesize, old_file)) != -1) {
    // If line is a file path (odd number)
    if ((count % 2) != 0) {
      // Save file path to a temp location
      file_path = strdup(line);
      // For every file in filelist
      for (int a = 0; a < counter; a++) {
        // If the file path and file list equal
        if (!strcmp(file_path, filelist[a]) {
          // Increase count by two
          // This will skip over both the file path and the words in said file
          count = count + 2;
          continue;
        }
      }
      // If the file path is not to be removed add it to the new file
      fprintf(new_file, "%s\n", file_path);
      count++;
      continue;
    }
    // File path must be true - add all words to next line
    else {
      fprintf(new_file, "%s\n", line);
      count++;
    }
  // Remove old file
  remove(to_be_removed_file);
  // Rename new file as old file name
  rename(temp_file_name, to_be_removed_file);
  fclose(new_file);
  fclose(old_file);
}
