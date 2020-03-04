CC=g++ -std=c++11

all: calc test_calc

run: calc
	./calc

test: test_calc
	./test_calc	

calc: main.o 
	$(CC) -o calc main.o 

test_calc: test_calc.o 
	$(CC) -o test_calc test_calc.o 

main.o: main.cpp calc.hpp
	$(CC) -c main.cpp

test_calc.o: test_calc.cpp calc.hpp	
	$(CC) -c test_calc.cpp

clean:
	rm -rf *.o calc test_calc