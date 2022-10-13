//FUNCTIONS FOR FINDING WORDS WITHIN FILES
#include "trove.h"

void read_file(char *filename) {
  char *buf;
  char *line; 
  FILE *fp = fopen(filename, "r");
  FILE *trovefile = append_trove(fs->file_name);
  // fopen failed
  if (fp == NULL) {
    perror(progname);
    exit(EXIT_FAILURE);
  }
  // if append_trove failed
  if (trovefile == NULL) {
    perror(progname);
    exit(EXIT_FAILURE);
  }
  // While there are lines within the file
  while (fgets(&line, sizeof line, fp) != NULL {
    // Make each non-alpha character a space
    for (char *temp = line; *temp; temp++) {
      if (!isalpha(*temp)) {
        *temp = ' ';
      }
    }
    // Grab the alphanumeric word
    buf = strtok(line, ' ');
    // While the buffer has a word
    while (buf != NULL) {
      // If buffered word is bigger than min length
      if (strlen(buf) >= min_word_length) {
        // Add word to buffer
        fprintf(trovefile, "%s ", buf);
      }
      // Grab next tokenised word
      buf = strtok(NULL, ' ');
    }
  }
  fprintf(trovefile, "\n");
  fclose(fp);
  fclose(trovefile);
}
