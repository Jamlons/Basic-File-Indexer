//FUNCTIONS FOR FINDING WORDS WITHIN FILES
#include "trove.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <ctype.h>

typedef struct {
  int wordcounter;
  char * wordlist[];
}WORD_STRUCTURE;

WORD_STRUCTURE ws;

// Function for adding all words of a given file of a given length to a given file
void read_file(FILE *build_pointer, char *filename) {
  printf("Grabbing words\n");
  // Global structure
  //READ_FILE_STRUCTURE *rfs = &read_file_structure;
  ws.wordcounter = 0;
  char *buf;
  char *line = NULL;
  size_t linesize = 0;
  ssize_t linelen;
  FILE *fp = fopen(filename, "r");
  int number_of_words = 0;
  // fopen failed
  if (fp == NULL) {
    perror(progname);
    exit(EXIT_FAILURE);
  }
  // While there are lines to get from text file
  while ((linelen = getline(&line, &linesize, fp)) != -1) {
    int flag = 0;
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
      number_of_words++;
      //printf("Word is %s\n", buf);
      //Make all words lowercase
      int length = strlen(buf);
      char *lowercase = malloc(length + 1);
      lowercase[length] = 0;
      for (int i = 0; i < length; i++) {
        lowercase[i] = tolower(buf[i]);
      }
      for (int y = 0; y < ws.wordcounter; y++) {
        if (!strcmp(ws.wordlist[y], lowercase)) {
          flag = 1;
        }
      }
      if (!flag) {
        ws.wordlist[ws.wordcounter] = strdup(lowercase);
        ws.wordcounter++;
        fprintf(build_pointer, "%s ", lowercase);
        buf = strtok(NULL, " ");
      }
      else
        buf = strtok(NULL, " ");
    }
  }
  // Add a new line to the end of the line
  fprintf(build_pointer, "\n");
  printf("Words found: %d\n", number_of_words);
  printf("Words saved: %d\n", ws.wordcounter);
  free(line);
  fclose(fp);
}
