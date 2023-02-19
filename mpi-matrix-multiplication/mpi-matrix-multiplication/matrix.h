/*
 * File name: matrix.h
 * Roles: Header file for the matrix operation functions
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

/*
 * memory_allocate: Allocate memory for the matrix
 *  Parameters:
 *   int size: size of the matrix
 *   int** matrix: double pointer to the matrix
 *  Return: None
 */
void memory_allocate(int size, int **matrix);

/*
 * memory_deallocate: Deallocate memory for the matrix
 *  Parameters:
 *   int** matrix: double pointer to the matrix
 *  Return: None
 */
void memory_deallocate(int **matrix);

/*
 * init: Initialize the matrix with 0's
 *  Parameters:
 *   int matrix_size: size of the matrix
 *   int* matrix: pointer to the matrix
 *  Return: None
 */
void init(int matrix_size, int *matrix);

/*
 * dimension: Get the number of rows and columns of the matrix
 *  Parameters:
 *   FILE* fp: pointer to the input file
 *   int* row: pointer to the number of rows
 *   int* col: pointer to the number of columns
 *  Return: None
 */
void dimension(FILE *fp, int *row, int *col);

/*
 * element: Get the elements of the matrix
 *  Parameters:
 *   FILE* fp: pointer to the input file
 *   int matrix_size: size of the matrix
 *   int* matrix: pointer to the matrix
 *  Return: None
 */
void element(FILE *fp, int matrix_size, int *matrix);

/*
 * print: Print the matrix
 *  Parameters:
 *   int row: number of rows of the matrix
 *   int col: number of columns of the matrix
 *   double* matrix: pointer to the matrix
 *  Return: None
 */
void print(int row, int col, int *matrix);

/*
 * row_per_process: Calculate the number of rows for each process
 *  Parameters:
 *   int size: total number of processes
 *   int rank: rank of the current process
 *   int rows: number of rows of the matrix
 *  Return: Number of rows for each process
 */
int row_per_process(int size, int rank, int rows);

/*
 * vector_variant: Calculate the number of elements
 * and the displacement for each process
 *  Parameters:
 *   int size: total number of processes
 *   int rows: number of rows of the matrix
 *   int cols: number of columns of the matrix
 *   int* count: pointer to the number of elements for each process
 *   int* displacement: pointer to the displacement for each process
 *  Return: None
 */
void vector_variant(  //
    int size,         // in
    int rows,         // in
    int cols,         // in
    int *count,       // out
    int *displacement // out
);

/*
 * multiply: Multiply two matrices
 *  Parameters:
 *   int colA: number of columns of the first matrix
 *   int colB: number of columns of the second matrix
 *   int sizeC: size of the result matrix
 *   int* matrixA: pointer to the first matrix
 *   int* matrixB: pointer to the second matrix
 *   int* matrixC: pointer to the result matrix
 *  Return: None
 */
void multiply(    //
    int colA,     // in
    int colB,     // in
    int sizeC,    // in
    int *matrixA, // in
    int *matrixB, // in
    int *matrixC  // out
);

#endif
