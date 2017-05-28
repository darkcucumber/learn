CCFLAGS = -O2 -fpic -std=c++14

all: SparseLib main

SparseLib: SparseArrays.o
	g++ $< -shared -o libsparse.so 

SparseArrays.o: SparseArrays.cpp
	g++ $< $(CCFLAGS) -c

install: libsparse.so
	sudo cp $< /usr/lib

main: SparseLib
	g++  -I . -L /home/jakub/learn/hacker_rank/SparseArrays $(CCFLAGS) -o main main.cpp -lsparse

clean: 
	rm -f SparseArrays.o SparseArrays.so main.o main