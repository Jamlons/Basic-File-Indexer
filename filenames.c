//FUNCTION FOR FINDING THE GIVEN WORD WITHIN THE GIVEN TROVEFILE
#include "trove.h"
#include <string.h>
#include <stdio.h>

int find_names(FILE *fp) {
  READ_FILE_STRUCTURE *rfs = &read_file_structure;
  int amount_of_files_found = 0;
  char *buf;
  char *line = NULL;
  char * file_path = NULL;
  size_t linesize = 0;
  ssize_t linelen;
  int count = 1;
  // While grabbing each line from the file
  while ((linelen = getline(&line, &linesize, fp)) != -1) {
    //printf("Count is: %d\n", count);
    if ((count % 2) != 0) {
      //printf("Grabbing file path\n");
      file_path = strdup(line);
      //printf("File path is: %s\n", file_path);
      count++;
      continue;
    }
    count++;
    //printf("\nGrabbing Line\n");
    //printf("Word is: %s\n", rfs->word);
    //printf("Line is: %s\n", line);
    buf = strtok(line, " ");
    //printf("First word is: %s\n", buf);
    // Parse the line with a space token
    while (buf != NULL) {
      // While parsing through each word.
      char *temp = strdup(rfs->word);
      //printf("Word is: %s\n", buf);
      // If the parsed word does equal the word we are searching for
      if(!strcmp(temp, buf)) {
        // Print the word out
        //printf("\nFOUND WORD\n");
        //printf("Word found is: %s\n", buf);
        printf("%s\n", file_path);
        amount_of_files_found++;
        break;
      }
      buf = strtok(NULL, " ");
    }
  }
  return amount_of_files_found;
}
