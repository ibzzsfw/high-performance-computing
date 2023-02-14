#include <stdio.h>
#include <stdlib.h>

void memory_allocate(int size, double **matrix) {

  *matrix = (double *)malloc(size * sizeof(double));
}

void init(int size, double *matrix) {

  int i = 0;

  for (i = 0; i < size; i++) {
    matrix[i] = 0;
  }
}

void dimension(FILE *fp, int *row, int *col) {

  if (fscanf(fp, "%d %d", row, col) != 2) {
    printf("Error reading row and col.\n");
    fclose(fp);
    return;
  }
}

void element(FILE *fp, int size, double *matrix) {

  int i = 0;

  for (i = 0; i < size; i++) {
    if (fscanf(fp, "%lf", &matrix[i]) != 1) {
      printf("Error reading element.\n");
      fclose(fp);
      return;
    }
  }
}

void addition(       //
    int start_index, //
    int end_index,   //
    double *matrixA, //
    double *matrixB, //
    double *matrixC  //
) {

  int i = 0;

  for (i = start_index; i < end_index; i++) {
    matrixC[i] = matrixA[i] + matrixB[i];
  }
}

void print(int row, int col, double *matrix) {

  int i = 0;
  int j = 0;

  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      printf("%lf ", matrix[i * col + j]);
    }
    printf("\n");
  }
}

void range(           //
    int rows,         //
    int cols,         //
    int rank,         //
    int size,         //
    int *start_index, //
    int *end_index    //
) {

  int amount = rows * cols;
  int amount_per_process = amount / size;
  int remainder = amount % size;

  if (rank < remainder) {
    *start_index = rank * (amount_per_process + 1);
    *end_index = *start_index + amount_per_process + 1;
  } else {
    *start_index = rank * amount_per_process + remainder;
    *end_index = *start_index + amount_per_process;
  }
}
