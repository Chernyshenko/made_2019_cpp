CC=g++ -std=c++14

all: bigint test_bigint

run: bigint
	./bigint

test: test_bigint
	./test_bigint	

bigint: main.o BigInt.o
	$(CC) -o bigint main.o BigInt.o

test_bigint: test_BigInt.o
	$(CC) -o test_bigint test_BigInt.o BigInt.o

main.o: main.cpp BigInt.hpp 
	$(CC) -c main.cpp

BigInt.o: BigInt.cpp BigInt.hpp 
	$(CC) -c BigInt.cpp

test_BigInt.o: test_BigInt.cpp BigInt.hpp 	
	$(CC) -c test_BigInt.cpp

clean:
	rm -rf *.o bigint test_bigint