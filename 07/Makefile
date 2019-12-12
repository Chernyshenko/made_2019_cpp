CC=g++ -std=c++14

all: format test_format

run: format
	./format

test: test_format
	./test_format	

format: main.o format.o
	$(CC) -o format format.o main.o 

test_format: test_format.o format.o
	$(CC) -o test_format format.o test_format.o 

format.o: format.cpp format.hpp
	$(CC) -c format.cpp

main.o: main.cpp format.hpp
	$(CC) -c main.cpp

test_format.o: test_format.cpp format.hpp	
	$(CC) -c test_format.cpp

clean:
	rm -rf *.o format test_format