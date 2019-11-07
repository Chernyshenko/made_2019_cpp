CC=g++ -std=c++14

all: serialize test_serialize

run: serialize
	./serialize

test: test_serialize
	./test_serialize	

serialize: main.o
	$(CC) -o serialize main.o

test_serialize: testserialize.o
	$(CC) -o test_serialize testserialize.o

main.o: main.cpp serializer.hpp data.hpp
	$(CC) -c main.cpp

testserialize.o: testserialize.cpp serializer.hpp data.hpp 	
	$(CC) -c testserialize.cpp

clean:
	rm -rf *.o serialize test_serialize