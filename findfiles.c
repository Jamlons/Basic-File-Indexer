//FUNCTION FOR FINDING THE FILES WITHIN DIRECTORIES
#include "trove.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>

char * dirlist[];
int dircount = 1;

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
void list_directory(char *dirname) {
  dircount--;
  DIR *dirp;
  struct dirent *dp;
  dirp = opendir(dirname);
  // If we failed to open the directory
  if (dirp == NULL) {
	perror( progname );
	exit(EXIT_FAILURE);
  }
  // While directory stream is not null
  while((dp = readdir(dirp)) != NULL) {
	// Grab the file type
	int file_type = file_attributes(dp->d_name);
	// If file is regular
	if (file_type == 1) {
	  // Add information to the given file
	  FILE *fp = append_trove(dp->d_name);
	  printf("\n%s\n", dp->d_name);
	  add_file_path(fp, dp->d_name);
	  read_file(fp, dp->d_name);
	}
	// If file is a directory
	// THIS DOESN'T WORK PLEASE FIX
	else if (file_type == 2) {
	  printf("\n%s\n", "This is a directory");
	  dirlist[dircount] = strdup(dp->d_name);
 	  dircount++;
	}
	//File is neither file nor directory
	else {
	  printf("\n%s\n","File type not supported");
	  exit(EXIT_FAILURE);
	}
  }
  while (dircount != 0) {
	list_directory(dirlist[dircount]);
  }
  closedir(dirp);
}
