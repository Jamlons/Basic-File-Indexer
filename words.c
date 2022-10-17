//FUNCTIONS FOR FINDING WORDS WITHIN FILES
#include "trove.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function for adding all words of a given file of a given length to a given file
void read_file(FILE *build_pointer, char *filename) {
  // Global structure
  READ_FILE_STRUCTURE *rfs = &read_file_structure;
  char *buf;
  char *line = NULL;
  size_t linesize = 0;
  ssize_t linelen;
  FILE *fp = fopen(filename, "r");
  // fopen failed
  if (fp == NULL) {
    perror(progname);
    exit(EXIT_FAILURE);
  }
  // While there are lines to get from text file
  while ((linelen = getline(&line, &linesize, fp)) != -1) {
    // Make each non-alpha character a space
    for (char *temp = line; *temp; temp++) {
      if (!isalpha(*temp)) {
        *temp = ' ';
      }
    }
    // Grab the first word
    buf = strtok(line, " ");
    // While there are words to get
    while (buf != NULL) {
      // If the word isn't big enough skip
      if (strlen(buf) >= rfs->min_word_length) {
        // Add word to given text file
        fprintf(build_pointer, "%s ", buf);
      }
      buf = strtok(NULL, " ");
    }
  }
  // Add a new line to the end of the line
  fprintf(build_pointer, "\n");
  free(line);
  fclose(fp);
}
