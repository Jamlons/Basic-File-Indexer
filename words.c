//FUNCTIONS FOR FINDING WORDS WITHIN FILES
#include "trove.h"
#include <stdio.h>
#define BUFSIZE (sizeof(char) * 10000)

void read_file(char *filename) {
  char *buf;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
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
  while ((nread = getline(&line, &len, stream)) != -1) {
    // Make each non-alpha character a space
    for (char *temp = line; *temp; temp++) {
      if (!isalpha(*temp)) {
        *temp = ' ';
      }
    }
    buf = strtok(&line, ' ');
    
    while (buf != NULL) {
      if (strlen(buf) >= min_word_length) {
        fprintf(trovefile, "%s ", buf);
      }
      buf = strtok(NULL, ' ');
    }
  }
  fprintf(trovefile, "\n");
  fclose(fp);
  fclose(trovefile);
}
