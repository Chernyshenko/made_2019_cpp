#include <iostream>
#include <assert.h>

#include "ThreadPool.hpp"

void test_lambda(){
	ThreadPool pool(8);
	for (size_t i = 0; i < 10; i++){
		auto task = pool.exec([i]() {
			return i;
		});
		assert(task.get() == i);
	}
	std::cout << "test_lambda done\n";
}
int f1(int a){
	return a + 1;

}
void test_one_parameter(){
	ThreadPool pool(8);
	for (size_t i = 0; i < 10; i++){
		auto task = pool.exec(f1, i);
		assert(task.get() == i + 1);
	}
	std::cout << "test_one_parameter done\n";
}
int f2(int a, int b){
	return a * b;

}
void test_two_parameters(){
	ThreadPool pool(8);
	for (size_t i = 0; i < 10; i++){
		auto task = pool.exec(f2, i, i + 1);
		assert(task.get() == i*i + i);
	}
	std::cout << "test_two_parameters done\n";
}
int main(){
	test_lambda();
	test_one_parameter();
	test_two_parameters();
	return 0;
}