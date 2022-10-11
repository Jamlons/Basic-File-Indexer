#include "trove.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void file_attributes(char *filename) {
  struct stat stat_buffer;
  
  if(stat(filename, &stat_buffer) != 0) {
    perror(progname);
    exit(EXIT_FAILURE);
  }
  else if (S_ISREG(stat_buffer.st_mode)) {
    // Is a file - is readable 
  }
  else if (S_ISDIR(stat_buffer.st_mode)) {
    // Is a directory - is readable 
  }
}
