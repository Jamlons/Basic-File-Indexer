//FUNCTION TO REMOVE FILE INFO FROM GIVEN TROVEFILE
#include "trove.h"
#include "file_edits.h"

//To remove lines from files - must duplicate the text file without said lines in it
void remove_files(char *old_file_name, int counter, char *to_be_removed_file) {
  READ_FILE_STORAGE read_file_storage;
  FILE *new_file = create_trove('This_isAnObsurWeName_H90peuFully_en0uGh.txt');
  FILE *old_file = read_trove(old_file_name);
  if (new_file == NULL) {
    printf("Unable to open %s, weird...", 'This_isAnObsurWeName_H90peuFully_en0uGh.txt');
    perror(progname);
    exit(EXIT_FAILURE);
  }
  if (old_file == NULL) {
    printf("Unable to open %s, please make sure it is correct", old_file_name);
    perror(progname);
    exit(EXIT_FAILURE);
  }
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
  fclose(new_file);
  fclose(old_file);
}
