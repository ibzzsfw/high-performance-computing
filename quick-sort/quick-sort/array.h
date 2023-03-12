#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

void read_size(FILE *fp, int *size);

void read_array(FILE *fp, double *A, int n);

void memory_allocation(double **A, int n);

void memory_deallocation(double **A);

void init(double *A, int n);

void swap(double *a, double *b);

int hoare_partition(double *A, int l, int r);

void quick_sort(double *A, int l, int r);

void print_double(double *A, int n);
void print_int(int *A, int n);

void vector_variant(  //
    int p,            //
    int length,       //
    int *count,       //
    int *displacement //
);

void split_array( //
    double *A,    //
    int length,   //
    double pivot, //
    double **S,   //
    int *lengthS, //
    double **L,   //
    int *lengthL  //
);

void concat_array( //
    double *S,     //
    int lengthS,   //
    double *L,     //
    int lengthL,   //
    double *A      //
);

#endif