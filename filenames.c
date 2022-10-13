//FUNCTION FOR FINDING THE GIVEN WORD WITHIN THE GIVEN TROVEFILE
#include "trove.h"

int find_names(FILE *fp) {
  READ_FILE_STORAGE read_file_storage;
  int amount_of_files_found = 0;
  char *buf;
  char *line = NULL;
  char *file_path;
  size_t linesize = 0;
  ssize_t linelen;
  while ((linelen = getline(&line, &linesize, fp)) != -1) {
    buf = strtok(line, ' ');
    file_path = buf;
    while (buf != NULL) {
      buf = strtok(NULL, ' ');
      if(!strcmp(read_file_storage.word, buf) {
        printf("%s\n", file_path);
        amount_of_files_found++;
        break;
      }
    }  
  }
  close (line);
  return amount_of_files_found;
}
