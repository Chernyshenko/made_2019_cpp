CC=g++ -std=c++14

all: matrix test_matrix

run: matrix
	./matrix

test: test_matrix
	./test_matrix	

matrix: main.o matrix.o
	$(CC) -o matrix main.o matrix.o

test_matrix: testmatrix.o
	$(CC) -o test_matrix testmatrix.o matrix.o

main.o: main.cpp matrix.hpp 
	$(CC) -c main.cpp

matrix.o: matrix.cpp matrix.hpp 
	$(CC) -c matrix.cpp

testmatrix.o: testmatrix.cpp matrix.hpp 	
	$(CC) -c testmatrix.cpp

clean:
	rm -rf *.o matrix test_matrix