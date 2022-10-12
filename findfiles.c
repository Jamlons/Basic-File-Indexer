#include "trove.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int file_attributes(char *filename) {
  struct stat stat_buffer;
  
  if(stat(filename, &stat_buffer) != 0) {
    perror(progname);
    exit(EXIT_FAILURE);
  }
  // Is a file - is readable 
  else if (S_ISREG(stat_buffer.st_mode)) {
    return 1;
  }
  // Is a directory - is readable 
  else if (S_ISDIR(stat_buffer.st_mode)) {
    return 2;
  }
}

void list_directory(char *dirname) {
  DIR *dirp;
  struct dirent *dp;
  
  dirp = opendir(dirname);
  if (dirp == NULL) {
    perror( progname );
    exit(EXIT_FAILURE);
  }
  while((dp = readdir(dirp)) != NULL) {
     int file_type = file_attributes(dp->d_name);
     if (file_type = 1) {
       printf("\n%s\n", dp->d_name);
       read_file(dp->d_name);
     }
     else {
       printf("\n%s\n", "This is a directory");
       // Create a child process giving them the directory name
       // And going through list_directory again
     }
  }
  closedir(dirp);
}
