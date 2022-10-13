//FUNCTION FOR FINDING THE FILES WITHIN DIRECTORIES
#include "trove.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

// To see if file is a regular file or a directory
// Returns 1 if reg, returns 2 if dir
int file_attributes(char *filename) {
  struct stat stat_buffer;
  
  // Failed to open stat buffer for the given filename
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

// Lists every file or directory within a given directory
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
       add_file_path(dp->d_name);
       read_file(dp->d_name);
     }
     else {
       printf("\n%s\n", "This is a directory");
       switch (fork()) {
         case -1:
           printf("fork failed\n");
           exit(EXIT_FAILURE);
           break;
         case 0:
           list_directory(dp->d_name);
           break;
         default:
           int child, status;
           child = wait(&status);
           break;
       }
       // Create a child process giving them the directory name
       // And going through list_directory again
     }
  }
  closedir(dirp);
}
