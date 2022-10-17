//FUNCTIONS FOR FINDING WORDS WITHIN FILES
#include "trove.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void read_file(FILE *build_pointer, char *filename) {
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
  while ((linelen = getline(&line, &linesize, fp)) != -1) {
    // Make each non-alpha character a space
    for (char *temp = line; *temp; temp++) {
      if (!isalpha(*temp)) {
        *temp = ' ';
      }
    }
    buf = strtok(line, " ");
    
    while (buf != NULL) {
      if (strlen(buf) >= rfs->min_word_length) {
        fprintf(build_pointer, "%s ", buf);
      }
      buf = strtok(NULL, " ");
    }
  }
  fprintf(build_pointer, "\n");
  free(line);
  fclose(fp);
}
