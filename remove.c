//FUNCTION TO REMOVE FILE INFO FROM GIVEN TROVEFILE
#include "trove.h"
#include "file_edits.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//To remove lines from files - must duplicate the text file without said lines in it
void remove_files(char *old_file_name, int counter, char *to_be_removed_file) {
  READ_FILE_STRUCTURE *rfs = &read_file_structure;
  char *temp_file_name = "as239gnma9yhq9109k23.txt";
  FILE *new_file = create_trove(temp_file_name);
  FILE *old_file = read_trove(old_file_name);
  if (new_file == NULL) {
    printf("Unable to open %s, weird...", temp_file_name);
    perror(progname);
    exit(EXIT_FAILURE);
  }
  if (old_file == NULL) {
    printf("Unable to open %s, please make sure it is correct", old_file_name);
    perror(progname);
    exit(EXIT_FAILURE);
  }
  char *buf;
  char *line = NULL;
  size_t linesize = 0;
  ssize_t linelen;
  while ((linelen = getline(&line, &linesize, old_file)) != -1) {
    buf = strtok(line, " ");
    for (int x = 0; x <= counter; x++) {
      if (!strcmp(rfs->filelist[x], buf)) {
        break; 
      }
      else {
        fwrite(line, 1, sizeof(char), new_file);
      }
    }
  }
  remove(to_be_removed_file);
  rename(temp_file_name, to_be_removed_file);
  fclose(new_file);
  fclose(old_file);
}
