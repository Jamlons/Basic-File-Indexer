//FUNCTION TO REMOVE FILE INFO FROM GIVEN TROVEFILE
#include "trove.h"

//To remove lines from files - must duplicate the text file without said lines in it
void remove_files(FILE *fp, char *remove_file_name) {
  READ_FILE_STORAGE read_file_storage;
  FILE *new_file = create_trove('This_isAnObsurWeName_H90peuFully_en0uGh.txt');
  char *buf;
  char *line = NULL;
  char *file_path;
  size_t linesize = 0;
  ssize_t linelen;
  while ((linelen = getline(&line, &linesize, fp)) != -1) {
    buf = strtok(line, ' ');
    
  }
  close (line);
}
