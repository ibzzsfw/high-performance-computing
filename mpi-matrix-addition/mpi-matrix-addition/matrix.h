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
 *   double** matrix: double pointer to the matrix
 *  Return: None
 */
void memory_allocate(int size, double **matrix);

/*
 * init: Initialize the matrix with 0's
 *  Parameters:
 *   int matrix_size: size of the matrix
 *   double* matrix: pointer to the matrix
 *  Return: None
 */
void init(int matrix_size, double *matrix);

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
 *   double* matrix: pointer to the matrix
 *  Return: None
 */
void element(FILE *fp, int matrix_size, double *matrix);

/*
 * range: Calculate the range of elements for each process
 *  Parameters:
 *   int rows: number of rows of the matrix
 *   int cols: number of columns of the matrix
 *   int rank: rank of the current process
 *   int size: total number of processes
 *   int* start_index: pointer to the start index of the range
 *   int* end_index: pointer to the end index of the range
 *  Return: None
 */
void range(           //
    int rows,         //
    int cols,         //
    int rank,         //
    int size,         //
    int *start_index, //
    int *end_index    //
);

/*
 * addition: Perform matrix addition
 *  Parameters:
 *   int start_index: start index of the range
 *   int end_index: end index of the range
 *   double* matrixA: pointer to the first matrix
 *   double* matrixB: pointer to the second matrix
 *   double* matrixC: pointer to the result matrix
 *  Return: None
 */
void addition(       //
    int start_index, //
    int end_index,   //
    double *matrixA, //
    double *matrixB, //
    double *matrixC  //
);

/*
 * print: Print the matrix
 *  Parameters:
 *   int row: number of rows of the matrix
 *   int col: number of columns of the matrix
 *   double* matrix: pointer to the matrix
 *  Return: None
 */
void print(int row, int col, double *matrix);

#endif
