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
   printf("Compressing File...\n");
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
         dup2(thepipe[0], 0);   // Duplicate the reading descriptor and stdin
         close(thepipe[0]);     // Close the reading descriptor
         
         int check = execl("/usr/bin/gzip", "gzip", "-k", rfs->file_name, NULL);
         if (check == -1) {
            perror("/urs/bin/gzip");
            exit(EXIT_FAILURE);
         }
         printf("File compressed");
         break;
      default:
         break;
   }
}

//Returns file descriptor 
int read_compressed() {
   // Global structure
   READ_FILE_STRUCTURE *rfs = &read_file_structure;
   printf("Reading File...\n");
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
         close(thepipe[1]);     // Child will never read from pipe
         dup2(thepipe[0], 0);   // Duplicate the writing descriptor and stdout
         close(thepipe[0]);     // Close the writing descriptor
         
         // child may now read from its stdin (fd=0)
         
         // Execute new program terminating the child process
         execl("/usr/bin/zcat", "zcat", rfs->file_name, NULL);
         perror("/urs/bin/zcat");
         exit(EXIT_FAILURE);
         break;
      default:
         close(thepipe[0]);     // Child will never read from pipe
         dup2(thepipe[1], 1);   // Duplicate the writing descriptor and stdout
         close(thepipe[1]);     // Close the writing descriptor
         
         // parent may now write to its stdout (fd=1)
         
         break;
   }
   return 1;
}
