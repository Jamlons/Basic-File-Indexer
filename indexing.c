//FUNCTION FOR INDEXING FILE INFO
#include "trove.h"
#include  <stdio.h>
#include  <limits.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <sys/param.h>
#include  <dirent.h>
#include  <unistd.h>
// Not every library is needed - please remove

// Adds the full file path to the given trove file
void add_file_path(FILE *fp, char *file_name) {
   // Grab the resolved full path name
   char *resolved_path = get_resolved_path(file_name);
   // Add file path to text file
   fprintf(fp, "%s\n", resolved_path);  
}

char *get_resolved_path(char *file_name) {
   // Create a buffer that is the max limit a path can be
   char buf[PATH_MAX];
   // Grab the resolved full path name
   char *resolved_path = realpath(file_name, buf);
   if (resolved_path == NULL) {
      perror("realpath");
      exit(EXIT_FAILURE);
   }
   return resolved_path;
}

void compress_file() {
   // Global structure
   READ_FILE_STRUCTURE *rfs = &read_file_structure;
   int thepipe[2];
   char data[1024];
   int datasize, nbytes;
   if (pipe(thepipe) != 0) {
      printf("Cannot create pipe!");
      exit(EXIT_FAILURE);
   }
   switch (fork()) {
      // Fork Failed
      case -1:
         printf("fork() failed - Exiting!");
         exit(EXIT_FAILURE);
         break;
      // Child Process
      case 0:
         close(thepipe[1]);     // Child will never write to pipe
         dup2(thepipe[0], 0);   // duplicate the file stream
         close(thepipe[0]);     // Close the file stream
         
         int check = execl("/usr/bin/gzip", "gzip", rfs->file_name, NULL);
         if (check == -1) {
            perror("/urs/bin/gzip");
            exit(EXIT_FAILURE);
         }
         break;
      default:
         break;
   }
}
