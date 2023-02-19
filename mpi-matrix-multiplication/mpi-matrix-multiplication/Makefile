EXECUTABLES= multiplication

all : $(EXECUTABLES)

multiplication: multiplication.c matrix.c matrix.h util.c util.h
	mpicc $(CFLAGS) -o multiplication multiplication.c matrix.c util.c

clean:
	rm -f multiplication

# Path: Makefile