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
   // Create a buffer that is the max limit a path can be
   char buf[PATH_MAX];
   // Grab the resolved full path name
   char *resolved_path = realpath(file_name, buf);
   // If the pathname isn't empty add to text file
   if (resolved_path != NULL) {
      fprintf(fp, "%s ", resolved_path);  
   }
   else {
   // Otherwise break
      perror ("realpath");
      exit(EXIT_FAILURE);
   }
   fprintf(fp, "\n");
}
