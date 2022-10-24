//FUNCTION FOR FINDING THE GIVEN WORD WITHIN THE GIVEN TROVEFILE
#include "trove.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Find the word given by user within the File stream provided
// Returns 1 if a name is found, otherwise returns 0.
int find_names() {
  // Global Structure
  READ_FILE_STRUCTURE *rfs = &read_file_structure;
  // Read the compressed file
  read_compressed();
  int amount_of_files_found = 0;
  char *buf;
  char *line = NULL;
  char * file_path = NULL;
  size_t linesize = 0;
  ssize_t linelen;
  // Count for what line we are on
  int count = 1;
  // While grabbing each line from the file
  while ((linelen = getline(&line, &linesize, stdin)) != -1) {
    // If line is a filepath line (odd number)
    if ((count % 2) != 0) {
      // Copy the line to file_path and continue
      file_path = strdup(line);
      count++;
      continue;
    }
    count++;
    // Grab the first word with a space token
    buf = strtok(line, " ");
    // While parsing through each word.
    while (buf != NULL) {
      // Copy the word to a temp memory location, needs to work for strcmp to work
      int length = strlen(rfs->word);
      // Create a lowercase string for comparing
      char *lowercase = malloc(length + 1);
      // Add null character to terminate
      lowercase[length] = 0;
      // Make every character lowercase
      for (int i = 0; i < length; i++) {
        lowercase[i] = tolower(rfs->word[i]);
      }
      // If the parsed word does equal the word we are searching for
      if(!strcmp(lowercase, buf)) {
        // Print file path out and break out of the entire loop
        printf("%s", file_path);
        amount_of_files_found++;
        break;
      }
      // Find next word
      buf = strtok(NULL, " ");
    }
  }
  // Return 1 if file is found
  // Free all memory
  free(line);
  return amount_of_files_found;
}
