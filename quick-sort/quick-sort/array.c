#include <stdio.h>
#include <stdlib.h>

void read_size(FILE *fp, int *size) {

  if (fscanf(fp, "%d", size) != 1) {
    printf("Error reading size.\n");
    exit(1);
  }
}

void read_array(FILE *fp, double *A, int n) {

  int i = 0;

  for (i = 0; i < n; i++) {
    if (fscanf(fp, "%lf", &A[i]) != 1) {
      printf("Error reading array.\n");
      exit(1);
    }
  }
}

void memory_allocation(double **A, int n) {

  *A = (double *)malloc(n * sizeof(double));

  if (*A == NULL) {
    printf("Memory allocation failed.\n");
    exit(1);
  }
}

void memory_deallocation(double **A) {

  if (*A != NULL) {
    free(*A);
    *A = NULL;
  }
}

void init(double *A, int n) {

  int i = 0;

  for (i = 0; i < n; i++) {
    A[i] = 0.0;
  }
}

void swap(double *a, double *b) {
  double temp = *a;
  *a = *b;
  *b = temp;
}

int hoare_partition(double *A, int l, int r) {

  double p = A[r];
  int i = l - 1;
  int j = l;

  for (; j < r; j++) {
    if (A[j] <= p) {
      i++;
      swap(&A[i], &A[j]);
    }
  }

  swap(&A[i + 1], &A[r]);

  return (i + 1);
}

void quick_sort(double *A, int l, int r) {

  if (l < r) {
    int s = hoare_partition(A, l, r);
    quick_sort(A, l, s - 1);
    quick_sort(A, s + 1, r);
  }
}

void print_double(double *A, int n) {

  int i = 0;

  for (i = 0; i < n; i++) {
    printf("%lf\n", A[i]);
  }

  printf("\n");
}

void print_int(int *A, int n) {

  int i = 0;

  for (i = 0; i < n; i++) {
    printf("%d\n", A[i]);
  }

  printf("\n");
}

void vector_variant(  //
    int p,            //
    int length,       //
    int *count,       //
    int *displacement //
) {

  int i = 0;

  for (i = 0; i < p; i++) {
    count[i] = length / p;
    displacement[i] = i * count[i];
  }

  count[p - 1] += (length % p);
}

void split_array( //
    double *A,    //
    int length,   //
    double pivot, //
    double **S,   //
    int *lengthS, //
    double **L,   //
    int *lengthL  //
) {

  int i = 0;

  for (i = 0; i < length; i++) {
    if (A[i] <= pivot) {
      (*lengthS)++;
    } else {
      (*lengthL)++;
    }
  }

  memory_allocation(S, *lengthS);
  memory_allocation(L, *lengthL);

  int s = 0;
  int l = 0;

  for (i = 0; i < length; i++) {
    if (A[i] <= pivot) {
      (*S)[s] = A[i];
      s++;
    } else {
      (*L)[l] = A[i];
      l++;
    }
  }
}

void concat_array( //
    double *S,     //
    int lengthS,   //
    double *L,     //
    int lengthL,   //
    double *A      //
) {

  int i = 0;

  for (i = 0; i < lengthS; i++) {
    A[i] = S[i];
  }

  for (i = 0; i < lengthL; i++) {
    A[i + lengthS] = L[i];
  }
}