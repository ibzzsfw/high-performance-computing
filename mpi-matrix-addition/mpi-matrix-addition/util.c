#include <stdio.h>

void placeholder(char *str) { printf("%s\n", str); }

/*
file format for m[row][col]]:
row col
m[0][0] m[0][1] ... m[0][col-1]
m[1][0] m[1][1] ... m[1][col-1]
...
m[row-1][0] m[row-1][1] ... m[row-1][col-1]
*/

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

void write_txt(int row, int col, double *matrix, char *path) {

  FILE *fp = open_txt(path, "w");

  int i = 0;
  int j = 0;

  fprintf(fp, "%d %d\n", row, col);

  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      char *formatted = (j == col - 1) ? "%lf" : "%lf ";
      fprintf(fp, formatted, matrix[i * col + j]);
    }
    fprintf(fp, "\n");
  }
  printf("file written\n");
  fclose(fp);
}