//FUNCTION FOR FINDING THE GIVEN WORD WITHIN THE GIVEN TROVEFILE
#include "trove.h"
#include <string.h>
#include <stdio.h>

// Find the word given by user within the File stream provided
// Returns 1 if a name is found, otherwise returns 0.
int find_names(FILE *fp) {
  // Global Structure
  READ_FILE_STRUCTURE *rfs = &read_file_structure;
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
      char *temp = strdup(rfs->word);
      // If the parsed word does equal the word we are searching for
      if(!strcmp(temp, buf)) {
        // Print file path out and break out of the entire loop
        printf("%s", file_path);
        amount_of_files_found++;
        break;
      }
      buf = strtok(NULL, " ");
    }
  }
  // Return 1 if file is found
  return amount_of_files_found;
  fclose(fp);
}