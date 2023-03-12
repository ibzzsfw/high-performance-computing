#include "array.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double snapshot() { return (clock() / (double)CLOCKS_PER_SEC); }

int main(int argc, char *argv[]) {

  double start_init = 0.0;
  double end_init = 0.0;
  double start_read = 0.0;
  double end_read = 0.0;
  double start_sort = 0.0;
  double end_sort = 0.0;
  double start_write = 0.0;
  double end_write = 0.0;
  double start_deallocate = 0.0;
  double end_deallocate = 0.0;

  // argv[0] is the name of the program
  // argv[1] is the output file name

  start_init = clock() / (double)CLOCKS_PER_SEC;

  if (argc < 1) {
    printf("Usage: %s <input file name>\n", argv[0]);
    return (1);
  }

  int length = 0;
  double *array = NULL;
  char *inputPath = argv[1];
  char outputPath[20] = "\0";

  end_init = snapshot();

  start_read = snapshot();

  FILE *fp = open_txt(inputPath, "r");

  read_size(fp, &length);

  sprintf(outputPath, "output%d.txt", length);

  memory_allocation(&array, length);
  init(array, length);
  read_array(fp, array, length);

  fclose(fp);

  end_read = snapshot();

  start_sort = snapshot();
  quick_sort(array, 0, length - 1);
  end_sort = snapshot();

  start_write = snapshot();
  write_txt(array, length, outputPath);
  end_write = snapshot();

  start_deallocate = snapshot();
  memory_deallocation(&array);
  end_deallocate = snapshot();

  // printf("Time (s): intit, read, sort, write, deallocate\n");
  printf("%lf, %lf, %lf, %lf, %lf\n",      //
         end_init - start_init,            //
         end_read - start_read,            //
         end_sort - start_sort,            //
         end_write - start_write,          //
         end_deallocate - start_deallocate //
  );

  return (0);
}
