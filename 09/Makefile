CC=g++ -std=c++11 -pthread

all: ThreadPool test_ThreadPool

run: ThreadPool
	./ThreadPool

test: test_ThreadPool
	./test_ThreadPool	

ThreadPool: ThreadPool.o main.o 
	$(CC) -o ThreadPool main.o ThreadPool.o

test_ThreadPool: ThreadPool.o test_ThreadPool.o 
	$(CC) -o test_ThreadPool test_ThreadPool.o ThreadPool.o

main.o: main.cpp ThreadPool.hpp 
	$(CC) -c main.cpp

test_ThreadPool.o: test_ThreadPool.cpp ThreadPool.hpp 	
	$(CC) -c test_ThreadPool.cpp

ThreadPool.o: ThreadPool.cpp ThreadPool.hpp 	
	$(CC) -c ThreadPool.cpp

clean:
	rm -rf *.o ThreadPool test_ThreadPool