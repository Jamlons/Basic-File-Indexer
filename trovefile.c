#include "trove.h"

void create_trove(char *filename) {
  FILE *fp;
  fp = fopen(filename, "w");
  if (fp == NULL) {
    perror (progname);
    exit(EXIT_FAILURE);
  }
}
