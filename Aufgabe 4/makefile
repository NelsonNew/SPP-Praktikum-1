CC=gcc
CXX=g++
CFLAGS=-O2 -fopenmp -std=c99
CXXFLAGS=-O2 -fopenmp
EXECS= heated-plate-parallel

all: $(EXECS)

heated-plate-parallel: heated-plate-parallel.cpp  
	$(CXX) -o $@ $< $(CXXFLAGS)
clean:
	rm -f $(EXECS) *.o