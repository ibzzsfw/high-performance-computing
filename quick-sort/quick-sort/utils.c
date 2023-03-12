#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE *open_txt(char *path, char *mode) {

  printf("path: %s\n", path);

  FILE *fp = fopen(path, mode);
  if (fp == NULL) {
    printf("Error opening file.\n");
    return NULL;
  }

  printf("file opened\n");

  return (fp);
}

void write_txt(double *array, int size, char *path) {

  FILE *fp = open_txt(path, "w");

  fprintf(fp, "%d\n", size);

  for (int i = 0; i < size; i++) {
    fprintf(fp, "%lf\n", array[i]);
  }

  printf("file written\n");
  fclose(fp);
}

void random_txt(int size) {

  // fileaname = random<length>.txt
  char filename[20];
  sprintf(filename, "random%d.txt", size);

  FILE *fp = open_txt(filename, "w");

  fprintf(fp, "%d\n", size);
  srand(time(NULL));
  for (int i = 0; i < size; i++) {
    double r = (double)rand() / (double)RAND_MAX;
    fprintf(fp, "%lf\n", r);
  }

  printf("file written\n");
  fclose(fp);
}