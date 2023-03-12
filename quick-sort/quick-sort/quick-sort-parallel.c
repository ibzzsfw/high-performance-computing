#include "array.h"
#include "mpi.h"
#include "parallel.h"
#include "utils.h"
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define MASTER 0

int main(int argc, char *argv[]) {
  // Initialize MPI
  MPI_Init(&argc, &argv);

  // Get the number of processes
  int p = 0;
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  // Get the rank of the process
  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  double start = 0.0;
  double end = 0.0;

  if (rank == MASTER) {
    start = MPI_Wtime();
  }

  if (argc < 2) {
    if (rank == 0) {
      printf("Usage: %s <input file name> [<output file name>]\n", argv[0]);
    }
    MPI_Finalize();
    return (1);
  }

  double *A = NULL;
  int length = 0;

  char *inputPath = argv[1];
  char *outputPath;

  if (rank == MASTER) {

    FILE *file = open_txt(inputPath, "r");
    read_size(file, &length);
    memory_allocation(&A, length);
    read_array(file, A, length);
    fclose(file);
  }

  MPI_Bcast(&length, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
  if (rank != MASTER) {
    memory_allocation(&A, length);
  }
  MPI_Bcast(A, length, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);

  MPI_Qsort(A, length, MPI_COMM_WORLD);

  if (rank == MASTER) {

    write_txt(A, length, "output.txt");

    end = MPI_Wtime();
    printf("Time: %lf\n", end - start);
  }

  memory_deallocation(&A);

  MPI_Finalize();

  return (0);
}
