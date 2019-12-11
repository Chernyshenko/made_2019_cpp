CC=g++ -std=c++14

all: Vector test_Vector

run: Vector
	./Vector

test: test_Vector
	./test_Vector	

Vector: main.o Vector.o
	$(CC) -o Vector main.o

test_Vector: test_Vector.o
	$(CC) -o test_Vector test_Vector.o

main.o: main.cpp Vector.hpp 
	$(CC) -c main.cpp

test_Vector.o: test_Vector.cpp Vector.hpp 	
	$(CC) -c test_Vector.cpp

clean:
	rm -rf *.o Vector test_Vector