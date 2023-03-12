#ifndef PARALLEL_H
#define PARALLEL_H

#include "mpi.h"

void quick_sort_omp(double *A, int l, int r);

void MPI_Qsort(double *A, int length, MPI_Comm comm);

#endif