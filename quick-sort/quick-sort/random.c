#include "utils.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {

  // argv[0] is the name of the program
  // argv[1] is the size of the array

  int length = atoi(argv[1]);

  random_txt(length);

  return (0);
}
