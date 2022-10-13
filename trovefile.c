//FUNCTIONS FOR EDITING / READING / WRITING TO TROVE FILES
#include "trove.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

FILE *create_trove(char *trovename) {
  FILE *fp;
  fp = fopen(filename, "w+");
  if (fp == NULL) {
    perror (progname);
    exit(EXIT_FAILURE);
  }
  printf("File %s has been created", *trovename);
  return fp;
}

FILE *append_trove(char *filename) {
  FILE *fp;
  fp = fopen(filename, "a+");
  if (fp == NULL) {
    perror (progname);
    exit(EXIT_FAILURE);
  }
  return fp;
}

FILE *read_trove(char *filename) {
  FILE *fp;
  fp = fopen(filename, "r+");
  if (fp == NULL) {
    perror (progname);
    exit(EXIT_FAILURE);
  }
  return fp;
}
