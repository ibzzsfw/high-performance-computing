#include <stdio.h>

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

void write_txt(int row, int col, int *matrix, char *path) {

  FILE *fp = open_txt(path, "w");

  int i = 0;
  int j = 0;

  fprintf(fp, "%d %d\n", row, col);

  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      char *formatted = (j == col - 1) ? "%d" : "%d ";
      fprintf(fp, formatted, matrix[i * col + j]);
    }
    fprintf(fp, "\n");
  }
  printf("file written\n");
  fclose(fp);
}