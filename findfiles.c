//FUNCTION FOR FINDING THE FILES WITHIN DIRECTORIES
#include "trove.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int dircounter = 1;

// To see if file is a regular file or a directory
// Returns 1 if reg, returns 2 if dir
int file_attributes(char *filename) {
  struct stat stat_buffer;
  
  // Failed to open stat buffer for the given filename
  if(stat(filename, &stat_buffer) != 0) {
    perror( progname );
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
  return 0;
}

// Lists every file or directory within a given directory
void list_directory(char *dirname, FILE *text_pointer) {
  char fullpath[PATH_MAX];
  printf("Directory name is: %s\n", dirname);
  DIRECTORY_STRUCTURE *ds = &dir_struct;
  dircounter--;
  DIR *dirp;
  struct dirent *dp;
  dirp = opendir(dirname);
  if (dirp == NULL) {
    perror(progname);
    exit(EXIT_FAILURE);
  }

  while((dp = readdir(dirp)) != NULL) {
    printf("dp name is: %s\n", dp->d_name);
    if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) {
     continue;
    }
    sprintf(fullpath, "%s/%s", dirname, dp->d_name);
    printf("Full path is: %s\n", fullpath);
    int file_type = file_attributes(fullpath);
    if (file_type == 1) {
      printf("File is a reg\n");
      add_file_path(text_pointer, fullpath);
      read_file(text_pointer, fullpath);
    }
    else if (file_type == 2) {
      printf("File is a dir\n");
      printf("Dir counter is: %d\n", dircounter);
      ds->dirlist[dircounter] = strdup(fullpath);
      dircounter++;
      printf("Dir counter is: %d\n", dircounter);
    }
    else {
      printf("Unknown\n");
    }
  }
  while (dircounter >= 0) {
    dircounter--;
    printf("Dir counter is: %d\n", dircounter);
    printf("Full path is: %s\n", ds->dirlist[dircounter]);
    printf("\nCalling Function Again!\n");
    list_directory(ds->dirlist[dircounter], text_pointer);
  }
  closedir(dirp);

}