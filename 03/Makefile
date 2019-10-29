CC=g++ -std=c++14

all: parser test_parser

run: parser
	./parser

test: test_parser
	./test_parser	

parser: main.o parser.o
	$(CC) -o parser main.o parser.o

test_parser: testParser.o
	$(CC) -o test_parser testParser.o parser.o

main.o: main.cpp parser.hpp 
	$(CC) -c main.cpp

parser.o: parser.cpp parser.hpp 
	$(CC) -c parser.cpp

testParser.o: testParser.cpp parser.hpp 	
	$(CC) -c testParser.cpp

clean:
	rm -rf *.o parser test_parser