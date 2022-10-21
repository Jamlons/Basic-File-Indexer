//FUNCTIONS FOR FINDING WORDS WITHIN FILES
#include "trove.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function for adding all words of a given file of a given length to a given file
void read_file(FILE *build_pointer, char *filename) {
  //READ_FILE_STRUCTURE *rfs = &read_file_structure;
  // Global structure
  //int wordcounter = 0;
  //int flag = 0;
  //int counter = 0;
  char *buf;
  char *line = NULL;
  // Array of pointers to strings
  char ** words;
  words = malloc(10000 * sizeof(char *));
  int word_length = 0;
  int number_of_words = 0;
  int number_of_words_found = 0;
  int flag = 0;
  int realloc_count = 1;
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
      if (!isalnum(*temp)) {
        *temp = ' ';
      }
    }
    // Grab the first word
    buf = strtok(line, " ");
    // While there are words to get
    while (buf != NULL) {
      int length = strlen(buf);
      char *lowercase = malloc(length + 1);
      lowercase[length] = 0;
      for (int i = 0; i < length; i++) {
        lowercase[i] = tolower(buf[i]);
      }
      number_of_words_found++;
      word_length = strlen(lowercase);
      for (int i = 0; i < number_of_words; i++) {
        if (!strcmp(lowercase, words[i])) {
          flag = 1;
          break;
        }
      }
      if (number_of_words >= 10000) {
        realloc_count++;
        words = realloc(words, 10000 * sizeof(char *) * realloc_count);
      }
      if (!flag) {
        words[number_of_words] = malloc(word_length * sizeof(char));
        strcpy(words[number_of_words], lowercase);
        number_of_words++;
      }
      fprintf(build_pointer, "%s ", lowercase);
      buf = strtok(NULL, " ");
    }
  //printf("Words found: %d\n", counter);
  //printf("Words added to file: %d\n", wordcounter);
  // Add a new line to the end of the line
  }
  printf("Number of words found was: %d\n", number_of_words_found);
  printf("Number of words saved is: %d\n", number_of_words);
  fprintf(build_pointer, "\n");
  for (int a = 0; a < number_of_words; a++) {
    free(words[a]);
  }
  free(line);
  fclose(fp);
}