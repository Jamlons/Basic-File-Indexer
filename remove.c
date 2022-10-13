//FUNCTION TO REMOVE FILE INFO FROM GIVEN TROVEFILE
#include "trove.h"

//To remove lines from files - must duplicate the text file without said lines in it
void remove_files(FILE *fp, int counter, char *to_be_removed_file) {
  READ_FILE_STORAGE read_file_storage;
  FILE *new_file = create_trove('This_isAnObsurWeName_H90peuFully_en0uGh.txt');
  int a;
  char *buf;
  char *line = NULL;
  char *file_path;
  size_t linesize = 0;
  ssize_t linelen;
  while ((linelen = getline(&line, &linesize, fp)) != -1) {
    buf = strtok(line, ' ');
    for (int x = 0; x <= counter; x++) {
      if (!strcmp(filelist[x], buf) {
        break; 
      }
      else {
        fwrite(line, nread, 1, new_file);
      }
    }
  }
  remove(to_be_removed_file);
  rename('This_isAnObsurWeName_H90peuFully_en0uGh.txt', to_be_removed_file);
  close (line);
}
