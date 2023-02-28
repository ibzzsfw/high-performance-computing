EXECUTABLES= sequential

all : $(EXECUTABLES)

sequential: sequential.c matrix.c matrix.h util.c util.h
	gcc $(CFLAGS) -o sequential sequential.c matrix.c util.c

clean:
	rm -f sequential

# Path: Makefile