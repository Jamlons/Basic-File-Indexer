//FUNCTION FOR INDEXING FILE INFO
#include "trove.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

// Adds the full file path to the given trove file
void add_file_path(FILE *fp, char *file_name) {
   // Grab the resolved full path name
   char *resolved_path = get_resolved_path(file_name);
   // Add file path to text file
   fprintf(fp, "%s\n", resolved_path);  
}
// Returns the full resolved file path
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
// Compresses TroveFile
void compress_file() {
   // Global structure
   READ_FILE_STRUCTURE *rfs = &read_file_structure;
   int thepipe[2];
   // Create a pipe
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
         
         // child may now read from its stdin (fd=0)
         // Call the gzip utility on the filename
         execl("/usr/bin/gzip", "gzip", "-f", rfs->file_name, NULL);
         perror("/urs/bin/gzip");
         exit(EXIT_FAILURE);
         printf("File compressed\n");
         break;
      // As a parent don't do anything
      default:
         break;
   }
}
// Uncompresses TroveFile
// Allows for the uncompresssed stream to be read from stdin
void read_compressed() {
   // Global structure
   READ_FILE_STRUCTURE *rfs = &read_file_structure;
   int thepipe[2];
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
         close(thepipe[0]);     // Child will never read from pipe
         dup2(thepipe[1], 1);   // Duplicate the writing descriptor and stdout
         close(thepipe[1]);     // Close the writing descriptor
         
         // child may now write from its stdin (fd=1)
         // Execute new program terminating the child process
         char full_path[PATH_MAX];
         // Grab full path name while adding .gz at the end for the zcat function
         sprintf(full_path, "%s.%s", rfs->file_name, "gz");
         // Call zcat function
         execl("/usr/bin/zcat", "zcat", full_path, NULL);
         perror("/urs/bin/zcat");
         exit(EXIT_FAILURE);
         break;
      // Parent Process
      default:
         close(thepipe[1]);     // Child will never read from pipe
         dup2(thepipe[0], 0);   // Duplicate the writing descriptor and stdout
         close(thepipe[0]);     // Close the writing descriptor
         
         // parent may now write to its stdin (fd=0)
         break;
   }
}