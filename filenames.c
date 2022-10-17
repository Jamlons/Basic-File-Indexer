//FUNCTION FOR FINDING THE GIVEN WORD WITHIN THE GIVEN TROVEFILE
#include "trove.h"
#include <string.h>
#include <stdio.h>

int find_names(FILE *fp, char *word) {
  int amount_of_files_found = 0;
  char *buf;
  char *line = NULL;
  char *file_path;
  size_t linesize = 0;
  ssize_t linelen;
  // While grabbing each line from the file
  while ((linelen = getline(&line, &linesize, fp)) != -1) {
    // Parse the line with a space token - first one is the filepath 
    //(this wont work if the filepath includes spaces)
    buf = strtok(line, " ");
    file_path = buf;
    while (buf != NULL) {
      // While parsing through each word.
      buf = strtok(NULL, " ");
      // If the parsed word does equal the word we are searching for
      if(!strcmp(word, buf)) {
        // Print the word out
        printf("%s\n", file_path);
        amount_of_files_found++;
        break;
      }
    }  
  }
  return amount_of_files_found;
}
