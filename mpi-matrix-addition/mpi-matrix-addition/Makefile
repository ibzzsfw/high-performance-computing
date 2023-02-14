EXECUTABLES= blocking non-blocking

all : $(EXECUTABLES)

blocking: blocking.c matrix.c matrix.h util.c util.h
	mpicc $(CFLAGS) -o blocking blocking.c matrix.c util.c

non-blocking: non-blocking.c matrix.c matrix.h util.c util.h
	mpicc $(CFLAGS) -o non-blocking non-blocking.c matrix.c util.c

clean:
	rm -f blocking non-blocking

# Path: Makefile