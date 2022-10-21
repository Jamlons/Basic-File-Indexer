//FUNCTIONS FOR FINDING WORDS WITHIN FILES
#include "trove.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function for adding all words of a given file of a given length to a given file
void read_file(FILE *build_pointer, char *filename) {
  READ_FILE_STRUCTURE *rfs = &read_file_structure;
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
    // Make each non-alphanumeric character a space
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
      // Create a lowercase string for storage
      char *lowercase = malloc(length + 1);
      lowercase[length] = 0;
      // Make every character lowercase
      for (int i = 0; i < length; i++) {
        lowercase[i] = tolower(buf[i]);
      }
      number_of_words_found++;
      word_length = strlen(lowercase);
      if (word_length < rfs->min_word_length) {
        buf = strtok(NULL, " ");
        continue;
      }
      // For every word stored, if a word matches break
      for (int i = 0; i < number_of_words; i++) {
        if (!strcmp(lowercase, words[i])) {
          flag = 1;
          break;
        }
      }
      // If running out of memory
      if (number_of_words >= 9999) {
        realloc_count++;
        // Reallocate more
        words = realloc(words, 10000 * sizeof(char *) * realloc_count);
      }
      // If no words match
      if (!flag) {
        words[number_of_words] = malloc(word_length * sizeof(char));
        strcpy(words[number_of_words], lowercase);
        fprintf(build_pointer, "%s ", lowercase);
        number_of_words++;
      }
      buf = strtok(NULL, " ");
    }
  }
  printf("For file name %s\n", filename);
  // Print every word found
  printf("Number of words found was: %d\n", number_of_words_found);
  // Print every word saved
  printf("Number of words saved is: %d\n", number_of_words);
  fprintf(build_pointer, "\n");
  // Free all memory
  for (int a = 0; a < number_of_words; a++) {
    free(words[a]);
  }
  free(line);
  fclose(fp);
}