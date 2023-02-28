#include "matrix.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

  // argc[0] is the program name
  // arcg[1] is the matrix A file path
  // arcg[2] is the matrix B file path
  // argc[3] is the matrix C file path

  double start_time = 0.0;
  double end_time = 0.0;

  // start observing time
  start_time = clock() / (double)CLOCKS_PER_SEC;

  if (argc < 3) {
    return (1);
  }

  double start_initialize = 0.0;
  double end_initialize = 0.0;

  start_initialize = clock() / (double)CLOCKS_PER_SEC;

  int rowA = 0;
  int colA = 0;
  int rowB = 0;
  int colB = 0;
  int sizeA = 0;
  int sizeB = 0;
  int sizeC = 0;
  int *matrixA = NULL;
  int *matrixB = NULL;
  int *matrixC = NULL;

  end_initialize = clock() / (double)CLOCKS_PER_SEC;

  char *pathA = argv[1];
  char *pathB = argv[2];
  char *pathC = argv[3];

  FILE *fpA = open_txt(pathA, "r");
  FILE *fpB = open_txt(pathB, "r");

  if (fpA == NULL || fpB == NULL) {
    printf("Error opening file(s).\n");
    return (1);
  }

  dimension(fpA, &rowA, &colA);
  dimension(fpB, &rowB, &colB);

  // check if matrix A and B are compatible for multiplication
  if (colA != rowB) {
    printf("Matrix A and B are not compatible for multiplication.\n");
    return (1);
  }

  sizeA = rowA * colA;
  sizeB = rowB * colB;
  sizeC = rowA * colB;

  // allocate memory for matrix A, B, and C
  memory_allocate(sizeA, &matrixA);
  element(fpA, sizeA, matrixA);
  // print(rowA, colA, matrixA);
  fclose(fpA);

  memory_allocate(sizeB, &matrixB);
  element(fpB, sizeB, matrixB);
  // print(rowB, colB, matrixB);
  fclose(fpB);

  memory_allocate(sizeC, &matrixC);

  double start_multiply = 0.0;
  double end_multiply = 0.0;

  start_multiply = clock() / (double)CLOCKS_PER_SEC;

  // matrix multiplication
  multiply(colA, colB, sizeC, matrixA, matrixB, matrixC);

  end_multiply = clock() / (double)CLOCKS_PER_SEC;

  // print(rowA, colB, matrixC);
  write_txt(rowA, colB, matrixC, pathC ? pathC : "output.txt");

  double start_deallocate = 0.0;
  double end_deallocate = 0.0;

  start_deallocate = clock() / (double)CLOCKS_PER_SEC;

  // deallocate memory
  rowA = 0;
  colA = 0;
  rowB = 0;
  colB = 0;
  sizeA = 0;
  sizeB = 0;
  sizeC = 0;

  memory_deallocate(&matrixA);
  memory_deallocate(&matrixB);
  memory_deallocate(&matrixC);

  end_deallocate = clock() / (double)CLOCKS_PER_SEC;

  // end observing time
  end_time = clock() / (double)CLOCKS_PER_SEC;

  printf("Time: %lf seconds\n", end_time - start_time);
  printf("Time: %lf seconds (initialize)\n", end_initialize - start_initialize);
  printf("Time: %lf seconds (multiply)\n", end_multiply - start_multiply);
  printf("Time: %lf seconds (deallocate)\n", end_deallocate - start_deallocate);
  start_time = 0.0;
  end_time = 0.0;
  start_initialize = 0.0;
  end_initialize = 0.0;
  start_multiply = 0.0;
  end_multiply = 0.0;
  start_deallocate = 0.0;
  end_deallocate = 0.0;

  return (0);
}
