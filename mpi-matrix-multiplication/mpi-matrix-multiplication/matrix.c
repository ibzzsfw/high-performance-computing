#include <stdio.h>
#include <stdlib.h>

void init(int size, int *matrix) {

  int i = 0;

  for (i = 0; i < size; i++) {
    matrix[i] = 0;
  }
}

void memory_allocate(int size, int **matrix) {

  *matrix = (int *)malloc(size * sizeof(int));
  if (*matrix == NULL) {
    printf("Error allocating memory.\n");
    return;
  }
  init(size, *matrix);
}

void memory_deallocate(int **matrix) {

  free(*matrix);
  *matrix = NULL;
  
}

void dimension(FILE *fp, int *row, int *col) {

  if (fscanf(fp, "%d %d", row, col) != 2) {
    printf("Error reading row and col.\n");
    fclose(fp);
    return;
  }
}

void element(FILE *fp, int size, int *matrix) {

  int i = 0;

  for (i = 0; i < size; i++) {
    if (fscanf(fp, "%d", &matrix[i]) != 1) {
      printf("Error reading element.\n");
      fclose(fp);
      return;
    }
  }
}

void print(int row, int col, int *matrix) {

  int i = 0;
  int j = 0;

  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      printf("%d ", matrix[i * col + j]);
    }
    printf("\n");
  }
}

void multiply(    //
    int colA,     //
    int colB,     //
    int sizeC,    //
    int *matrixA, //
    int *matrixB, //
    int *matrixC  //
) {

  int i = 0;
  int j = 0;
  int k = 0;

  for (i = 0; i < sizeC / colB; i++) {
    for (j = 0; j < colB; j++) {
      for (k = 0; k < colA; k++) {
        matrixC[i * colB + j] += matrixA[i * colA + k] * matrixB[k * colB + j];
      }
    }
  }
}

int row_per_process(int size, int rank, int rows) {

  int amount_per_process = rows / size;
  int remainder = rows % size;

  if (rank < remainder) {
    return amount_per_process + 1;
  } else {
    return amount_per_process;
  }
}

void vector_variant(  //
    int size,         //
    int rows,         //
    int cols,         //
    int *count,       //
    int *displacement //
) {

  int i = 0;

  for (i = 0; i < size; i++) {
    count[i] = row_per_process(size, i, rows) * cols;
    if (i == 0) {
      displacement[i] = 0;
    } else {
      displacement[i] = displacement[i - 1] + count[i - 1];
    }
  }
}