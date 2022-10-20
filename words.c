//FUNCTIONS FOR FINDING WORDS WITHIN FILES
#include "trove.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
  int temp;
  char * wordlist[];
}WORD_STRUCTURE;

WORD_STRUCTURE ws;

// Function for adding all words of a given file of a given length to a given file
void read_file(FILE *build_pointer, char *filename) {
  // Global structure
  READ_FILE_STRUCTURE *rfs = &read_file_structure;
  int wordcounter = 0;
  int flag = 0;
  int counter = 0;
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
    flag = 0;
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
      counter++;
      //printf("%s\n", buf);
      // If the word isn't big enough skip
      int length = strlen(buf);
      char *lowercase = malloc(length + 1);
      lowercase[length] = 0;
      for (int i = 0; i < length; i++) {
        lowercase[i] = tolower(buf[i]);
      }
      // Add word to given text file
      for (int y = 0; y < wordcounter; y++) {
        if ((!strcmp(ws.wordlist[y], lowercase)) && length >= rfs->min_word_length) {
          flag = 1;
          break;
        }
      }
      if (flag == 0) {
        fprintf(build_pointer, "%s ", lowercase);
        ws.wordlist[wordcounter] = strdup(lowercase);
        wordcounter++;
        buf = strtok(NULL, " ");
      }
      else {
        buf = strtok(NULL, " ");
      }
    }
  }
  printf("Words found: %d\n", counter);
  printf("Words added to file: %d\n", wordcounter);
  // Add a new line to the end of the line
  fprintf(build_pointer, "\n");
  free(line);
  fclose(fp);
}