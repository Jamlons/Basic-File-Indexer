#include "trove.h"
#include  <stdio.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <sys/param.h>
#include  <dirent.h>
#include  <unistd.h>

void create_file(char *filename) {
  FILE *fp;
  fp = fopen(filename, "w");
  if (fp == NULL) {
    perror (progname);
    exit(EXIT_FAILURE);
  }
}
