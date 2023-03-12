EXECUTABLES= quick-sort-sequential quick-sort-parallel random

all : $(EXECUTABLES)

quick-sort-sequential: quick-sort-sequential.c array.h array.c utils.h utils.c
	gcc $(CFLAGS) -fopenmp -o quick-sort-sequential quick-sort-sequential.c array.c utils.c

quick-sort-parallel: quick-sort-parallel.c array.h array.c utils.h utils.c parallel.h parallel.c
	mpicc $(CFLAGS) -fopenmp -o quick-sort-parallel quick-sort-parallel.c array.c utils.c parallel.c -lm

random: random.c utils.h utils.c
	gcc $(CFLAGS) -o random random.c utils.c

clean:
	rm -f quick-sort-sequential quick-sort-parallel random

# Path: Makefile