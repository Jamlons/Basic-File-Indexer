#include "trove.h"

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
