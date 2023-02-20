#include "matrix.h"
#include "util.h"
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MASTER 0

int main(int argc, char *argv[]) {

  // argc[0] is the program name
  // arcg[1] is the matrix A file path
  // arcg[2] is the matrix B file path
  // argc[3] is the matrix C file path

  // initialize MPI
  MPI_Init(&argc, &argv);

  // get the number of processes
  int size = 0;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // get the rank of the process
  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (argc < 3 && rank == MASTER) {
    MPI_Finalize();
    return (1);
  }

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
  int *subA = NULL;
  int *subC = NULL;
  int *countScatter = NULL;
  int *countGather = NULL;
  int *displacementScatter = NULL;
  int *displacementGather = NULL;
  double start_time = 0.0;
  double end_time = 0.0;

  memory_allocate(size, &countScatter);
  memory_allocate(size, &displacementScatter);
  memory_allocate(size, &countGather);
  memory_allocate(size, &displacementGather);

  // master process
  if (rank == MASTER) {

    char *pathA = argv[1];
    char *pathB = argv[2];

    FILE *fpA = open_txt(pathA, "r");
    FILE *fpB = open_txt(pathB, "r");

    if (fpA == NULL || fpB == NULL) {
      printf("Error opening file(s).\n");
      MPI_Finalize();
      return (1);
    }

    dimension(fpA, &rowA, &colA);
    dimension(fpB, &rowB, &colB);

    // check if matrix A and B are compatible for multiplication
    if (colA != rowB) {
      printf("Matrix A and B are not compatible for multiplication.\n");
      MPI_Finalize();
      return (1);
    }

    sizeA = rowA * colA;
    sizeB = rowB * colB;
    sizeC = rowA * colB;

    // calculate count and displacement
    vector_variant(size, rowA, colA, countScatter, displacementScatter);
    vector_variant(size, rowA, colB, countGather, displacementGather);

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

    // start timer, observe the time including synchronization
    start_time = MPI_Wtime();
  }

  // synchronize all processes to make sure that master process has finished
  // reading
  MPI_Barrier(MPI_COMM_WORLD);

  // broadcast matrix A dimension
  MPI_Bcast(&rowA, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
  MPI_Bcast(&colA, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

  // broadcast matrix B column and size
  MPI_Bcast(&colB, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
  MPI_Bcast(&sizeB, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

  // broadcast count and displacement
  MPI_Bcast(countScatter, size, MPI_INT, MASTER, MPI_COMM_WORLD);
  MPI_Bcast(displacementScatter, size, MPI_INT, MASTER, MPI_COMM_WORLD);
  MPI_Bcast(countGather, size, MPI_INT, MASTER, MPI_COMM_WORLD);
  MPI_Bcast(displacementGather, size, MPI_INT, MASTER, MPI_COMM_WORLD);

  // scatter matrix A
  memory_allocate(countScatter[rank], &subA);
  MPI_Scatterv(            //
      matrixA,             //
      countScatter,        //
      displacementScatter, //
      MPI_INT,             //
      subA,                //
      countScatter[rank],  //
      MPI_INT,             //
      MASTER,              //
      MPI_COMM_WORLD       //
  );

  // broadcast matrix B
  if (rank != MASTER) {
    memory_allocate(sizeB, &matrixB);
  }
  MPI_Bcast(matrixB, sizeB, MPI_INT, MASTER, MPI_COMM_WORLD);

  // allocate memory for subC
  memory_allocate(countGather[rank], &subC);

  // calculate subC
  multiply(colA, colB, countGather[rank], subA, matrixB, subC);

  // gather matrix C
  MPI_Gatherv(            //
      subC,               //
      countGather[rank],  //
      MPI_INT,            //
      matrixC,            //
      countGather,        //
      displacementGather, //
      MPI_INT,            //
      MASTER,             //
      MPI_COMM_WORLD      //
  );

  if (rank == MASTER) {
    end_time = MPI_Wtime();
    char *pathC = argv[3];
    // print(rowA, colB, matrixC);
    write_txt(rowA, colB, matrixC, pathC ? pathC : "output.txt");
    printf("Time: %lf milliseconds\n", (end_time - start_time) * 1000);
  }

  // deallocate memory
  memory_deallocate(&matrixA);
  memory_deallocate(&matrixB);
  memory_deallocate(&matrixC);
  memory_deallocate(&subA);
  memory_deallocate(&subC);

  // finalize MPI
  MPI_Finalize();

  return (0);
}
