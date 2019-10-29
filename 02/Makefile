CC=g++ -std=c++14

all: allocator test_allocator

run: 
	./allocator

test: test_allocator
	./test_allocator	

allocator: main.o 
	$(CC) -o allocator main.o

test_allocator: test.o
	$(CC) -o test_allocator test.o

main.o: main.cpp LinearAllocator.hpp 
	$(CC) -c main.cpp

test.o: test.cpp LinearAllocator.hpp 	
	$(CC) -c test.cpp

clean:
	rm -rf *.o allocator test_allocator