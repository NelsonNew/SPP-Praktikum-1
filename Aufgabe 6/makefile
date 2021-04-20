CC=gcc
CXX=g++
CFLAGS=-O2 -fopenmp -std=c99
CXXFLAGS=-O2 -fopenmp
EXECS= matrix-mult

all: $(EXECS)

matrix-mult: matrix-mult.c
	$(CC) -o $@ $<  $(CFLAGS)
clean:
	rm -f $(EXECS) *.o