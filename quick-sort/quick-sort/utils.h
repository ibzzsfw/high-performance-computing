#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

FILE *open_txt(char *path, char *mode);

void write_txt(double *array, int size, char *path);

void random_txt(int size);

#endif