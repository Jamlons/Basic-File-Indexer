//FUNCTIONS FOR EDITING / READING / WRITING TO TROVE FILES
#include "trove.h"
#include <stdlib.h>
#include <string.h>

// Function for returning a File Stream Pointer in Write+ mode for given filename
FILE *create_trove(char *trovename) {
  FILE *fp;
  fp = fopen(trovename, "w+");
  if (fp == NULL) {
    perror (progname);
    exit(EXIT_FAILURE);
  }
  printf("File %s has been created\n", trovename);
  return fp;
}
// Function for returning a File Stream Pointer in Append+ mode for given filename
FILE *append_trove(char *filename) {
  FILE *fp;
  fp = fopen(filename, "a+");
  if (fp == NULL) {
    perror (progname);
    exit(EXIT_FAILURE);
  }
  return fp;
}
// Function for returning a File Stream Pointer in Read+ mode for given filename
FILE *read_trove(char *filename) {
  FILE *fp;
  fp = fopen(filename, "r+");
  if (fp == NULL) {
    perror (progname);
    exit(EXIT_FAILURE);
  }
  return fp;
}