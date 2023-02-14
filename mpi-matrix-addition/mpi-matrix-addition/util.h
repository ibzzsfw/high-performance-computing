#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

/*
 * placeholder: This function is a placeholder for the functions that are not
 * implemented yet.
 *
 * Parameters:
 *  str: a pointer to a character array that represents the name of the
 * function.
 *
 * Return: None
 */
void placeholder(char *str);

/*
 * open_txt: This function opens a text file at the given path.
 *
 * Parameters:
 *  path: a pointer to a character array that represents the file path.
 *  mode: a pointer to a character array that represents the file mode.
 *
 * Return: a pointer to a FILE object.
 */
FILE *open_txt(char *path, char *mode);

/*
 * write_txt: This function writes the matrix to a text file at the given
 * path.
 *
 * Parameters:
 *  row: the number of rows of the matrix.
 *  col: the number of columns of the matrix.
 *  matrix: a pointer to the matrix.
 *  path: a pointer to a character array that represents the file path.
 *
 * Return: None
 */
void write_txt(int row, int col, double *matrix, char *path);

#endif
