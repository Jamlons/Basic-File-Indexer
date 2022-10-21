//FUNCTION TO REMOVE FILE INFO FROM GIVEN TROVEFILE
#include "trove.h"
#include "file_edits.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

//To remove lines from files - must duplicate the text file without said lines in it
void remove_files(int counter) {
  // Global structure
  READ_FILE_STRUCTURE *rfs = &read_file_structure;
  // Random file name
  char *temp_file_name = "as239gnma9yhq9109k23.txt";
  FILE *new_file = create_trove(temp_file_name);
  // Reading the compressed file
  read_compressed();
  char full_path[PATH_MAX];
  // Grab full path - adding .gz at the end
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
    // If line is a file path (odd number)
    if ((count % 2) != 0) {
      // Save file path to a temp location
      file_path = strdup(line);
      // Make '\n' character null
      file_path[strlen(file_path) - 1] = 0;
      // For every file in filelist
      for (int a = 0; a < counter; a++) {
        file_list_path = get_resolved_path(rfs->filelist[a]);
        // If the file path and file list equal
        if (!strcmp(file_path, file_list_path)) {
          // Increase count by two
          // This will skip over both the file path and the words in said file
          linelen = getline(&line, &linesize, stdin);
          // Why do we need this??? I can't figure out why it is needed for the remove function to work.
          flag = 1;
          continue;
        }
      }
      // If the file path is not to be removed add it to the new file
      if (flag)
        continue;
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