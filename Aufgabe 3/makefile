CC=gcc
CXX=g++
CFLAGS=-O2 -fopenmp -std=c99
CXXFLAGS=-O2 -fopenmp
EXECS= dotproduct

all: $(EXECS)

dotproduct: dotproduct.c
	$(CC) -o $@ $<  $(CFLAGS)
clean:
	rm -f $(EXECS) *.o