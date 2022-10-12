//FUNCTIONS FOR FINDING WORDS WITHIN FILES
#include "trove.h"

void read_file(char *filename) {
  char *buf;
  FILE *fp;
  char *line; 
  fp = fopen(filename, "r");
  // fopen failed
  if (fp == NULL){
   perror(progname);
    exit(EXIT_FAILURE);
  }
  // While there are lines within the file
  while (fgets(line, sizeof line, fp) != NULL {
    // Make each non-alpha character a space
    while (char *temp = line; *temp; temp++) {
      if (!isalpha(*temp))
        *temp = ' ';
    }
    // Grab the alphanumeric word
    buf = strtok(line, ' ');
    // While the buffer has a word
    while (buf != NULL) {
      // If buffered word is bigger than min length
      if (strlen(buf) >= min_word_length) {
      // this is a word that can now be saved for index.
      }
      // Grab next tokenised word
      buf = strtok(NULL, ' ');
    }
  }
}
