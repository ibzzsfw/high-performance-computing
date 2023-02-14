#include "matrix.h"
#include "util.h"
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define TOP_RANK 0

int main(int argc, char **argv) {

  // initialize MPI
  MPI_Init(&argc, &argv);

  // get the number of processes
  int size = 0;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // get the rank of the process
  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // argc[0] is the program name
  // arcg[1] is the matrix A file path
  // arcg[2] is the matrix B file path
  // argc[3] is the matrix C file path

  if (argc < 3 && rank == TOP_RANK) {
    // last argument is optional
    MPI_Finalize();
    return (1);
  }

  // top rank process
  if (rank == TOP_RANK) {
    char *pathA = argv[1];
    char *pathB = argv[2];
    char *pathC = argv[3];
    int rowA = 0;
    int colA = 0;
    int rowB = 0;
    int colB = 0;
    double *matrixA = NULL;
    double *matrixB = NULL;
    double *matrixC = NULL;
    double startTime = 0;
    double endTime = 0;

    // read matrix A file from path
    FILE *fpA = open_txt(pathA, "r");
    FILE *fpB = open_txt(pathB, "r");

    if (fpA == NULL || fpB == NULL) {
      printf("Error opening file(s).\n");
      return (1);
    }

    dimension(fpA, &rowA, &colA);
    dimension(fpB, &rowB, &colB);

    if (rowA != rowB || colA != colB) {
      printf("Error: matrix A and B must have the same dimension.\n");
      MPI_Finalize();
      return (1);
    }

    int matrix_size = rowA * colA;

    memory_allocate(matrix_size, &matrixA);
    init(matrix_size, matrixA);
    // print(rowA, colA, matrixA);
    element(fpA, matrix_size, matrixA);
    fclose(fpA);

    memory_allocate(matrix_size, &matrixB);
    init(matrix_size, matrixB);
    element(fpB, matrix_size, matrixB);
    // print(rowB, colB, matrixB);
    fclose(fpB);

    memory_allocate(matrix_size, &matrixC);
    init(matrix_size, matrixC);

    placeholder("start...\n");
    startTime = MPI_Wtime();

    // addition of matrix A and B in top rank process
    int start_index = 0;
    int end_index = 0;

    range(rowA, colA, rank, size, &start_index, &end_index);
    addition(start_index, end_index, matrixA, matrixB, matrixC);

    // in case we have more than one process
    if (size > 1) {

      // send part of matrix A and B to other processes
      for (int rank = 1; rank < size; rank++) {
        int start_index = 0;
        int end_index = 0;

        range(rowA, colA, rank, size, &start_index, &end_index);

        int amount = end_index - start_index;

        // send amount
        MPI_Send(&amount, 1, MPI_INT, rank, 0, MPI_COMM_WORLD);

        // send matrix A
        MPI_Send(&matrixA[start_index], amount, MPI_DOUBLE, rank, 1, MPI_COMM_WORLD);

        // send matrix B
        MPI_Send(&matrixB[start_index], amount, MPI_DOUBLE, rank, 2, MPI_COMM_WORLD);
      }

      // receive matrix C from other processes
      for (int rank = 1; rank < size; rank++) {
        int start_index = 0;
        int end_index = 0;

        range(rowA, colA, rank, size, &start_index, &end_index);
        int amount = end_index - start_index;

        // receive matrix C
        MPI_Recv(&matrixC[start_index], amount, MPI_DOUBLE, rank, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }
    }

    endTime = MPI_Wtime();
    printf("End...\nHosts: %d:\tTime: %f ms\n", size, (endTime - startTime) * 1000);

    // write matrix C to file
    write_txt(rowA, colA, matrixC, pathC ? pathC : "output.txt");

    // free memory
    free(matrixA);
    free(matrixB);
    free(matrixC);

    matrixA = NULL;
    matrixB = NULL;
    matrixC = NULL;

  } else {

    int amount = 0;
    double *matrixA = NULL;
    double *matrixB = NULL;
    double *matrixC = NULL;

    // receive amount
    MPI_Recv(&amount, 1, MPI_INT, TOP_RANK, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    memory_allocate(amount, &matrixA);
    memory_allocate(amount, &matrixB);
    memory_allocate(amount, &matrixC);

    // receive matrix A
    MPI_Recv(matrixA, amount, MPI_DOUBLE, TOP_RANK, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // receive matrix B
    MPI_Recv(matrixB, amount, MPI_DOUBLE, TOP_RANK, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // addition of matrix A and B in other processes
    addition(0, amount, matrixA, matrixB, matrixC);

    // send matrix C to top rank process
    MPI_Send(matrixC, amount, MPI_DOUBLE, TOP_RANK, 3, MPI_COMM_WORLD);

    // free memory
    free(matrixA);
    free(matrixB);
    free(matrixC);

    matrixA = NULL;
    matrixB = NULL;
    matrixC = NULL;
  }
  MPI_Finalize();
  return (0);
}