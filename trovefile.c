#include "trove.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

void create_trove(char *trovename) {
  FILE *fp;
  fp = fopen(filename, "w");
  if (fp == NULL) {
    perror (progname);
    exit(EXIT_FAILURE);
  }
  printf("File %s has been created", *trovename);
  fclose(fp);
}

FILE *open_trove(char *filename) {
  FILE *fp;
  fp = fopen(filename, "r+");
  if (fp == NULL) {
    perror (progname);
    exit(EXIT_FAILURE);
  }
  return fp;
}

FILE *read_trove(char *filename) {
  FILE *fp;
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror (progname);
    exit(EXIT_FAILURE);
  }
  return fp;
}
