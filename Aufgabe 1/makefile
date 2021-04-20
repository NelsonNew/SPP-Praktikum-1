CC=gcc
CXX=g++
CFLAGS=-O2 -fopenmp -std=c99
CXXFLAGS=-O2 -fopenmp
EXECS= hello-openmp

all: $(EXECS)

hello-openmp: hello-openmp.c
	$(CC) -o $@ $<  $(CFLAGS)
clean:
	rm -f $(EXECS) *.o