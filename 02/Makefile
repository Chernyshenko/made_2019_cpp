CC=g++ -std=c++11

all: allocator

allocator: main.o 
	$(CC) -o allocator main.o 

main.o: main.cpp LinearAllocator.hpp 
	$(CC) -c main.cpp

clean:
	rm -rf *.o allocator