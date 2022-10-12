//FUNCTION TO REMOVE FILE INFO FROM GIVEN TROVEFILE
#include "trove.h"

//To remove lines from files - must duplicate the text file without said lines in it
void remove_files(FILE *fp) {
  // If provided file isn't valid
  if (fp == NULL) {
   printf("Unable to open file given");
    perror(progname);
    exit(EXIT_FAILURE);
  }
  FILE *new_file = create_trove('tempfile.txt');
  // If unable to open tempfile
  if (new_file == NULL) {
    printf("Unable to open temp file, may not have permission");
    perror(progname);
    exit(EXIT_FAILURE);
  }
  while (!feof(fp)) {
  
  }
}
