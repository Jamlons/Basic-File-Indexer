//FUNCTION FOR FINDING THE FILES WITHIN DIRECTORIES
#include "trove.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int dircounter = 0;

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
  DIRECTORY_STRUCTURE *ds = &dir_struct;
  DIR *dirp;
  struct dirent *dp;
  dirp = opendir(dirname);
  if (dirp == NULL) {
    perror(progname);
    exit(EXIT_FAILURE);
  }

  while((dp = readdir(dirp)) != NULL) {
    // If the directory is linux storage for current directory or parent directory - skip
    if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) {
     continue;
    }
    // Grab the full path name of the file
    sprintf(fullpath, "%s/%s", dirname, dp->d_name);
    int file_type = file_attributes(fullpath);
    // If current file we are looking at is a regular file
    // Add it to the trovefile
    if (file_type == 1) {
      add_file_path(text_pointer, fullpath);
      read_file(text_pointer, fullpath);
    }
    // If current file we are looking at is a directory
    // Add it to dirlist
    else if (file_type == 2) {
      ds->dirlist[dircounter] = strdup(fullpath);
      dircounter++;
    }
    else {
      printf("Unknown\n");
    }
  }
  // While we still have directories not explored yet
  while (dircounter >= 0) {
    dircounter--;
    if (dircounter < 0) {
      break;
    }
    // Recursively call list_directory again
    list_directory(ds->dirlist[dircounter], text_pointer);
  }
  closedir(dirp);

}