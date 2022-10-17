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

void add_file_path(FILE *fp, char *file_name) {
   char buf[PATH_MAX];
   char *resolved_path = realpath(file_name, buf);
   printf("\nThis is the resolved path: %s\n", resolved_path);
   if (resolved_path != NULL) {
      fprintf(fp, "%s ", resolved_path);  
   }
   else {
      perror ("realpath");
      exit(EXIT_FAILURE);
   }
}
