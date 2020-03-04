#include <iostream>
#include <assert.h>
#include "calc.hpp"

void test_plus(){
	int err = 0;
	Calculator c("1 + 5");
	int res = c.Calc(err);
	assert(res == 6);
	std::cout << "test_plus OK\n";
}
void test_plus_minus(){
	int err = 0;
	Calculator c("1 + 5 - 7");
	int res = c.Calc(err);
	assert(res == -1);
	std::cout << "test_plus_minus OK\n";
}

void test_minus_minus(){
	int err = 0;
	Calculator c("1 - -7");
	int res = c.Calc(err);
	assert(res == 8);
	std::cout << "test_minus_minus OK\n";
}
void test_mult(){
	int err = 0;
	Calculator c("2 *-7");
	int res = c.Calc(err);
	assert(res == -14);
	std::cout << "test_mult OK\n";
}
void test_divide(){
	int err = 0;
	Calculator c("14 / 7");
	int res = c.Calc(err);
	assert(res == 2);
	std::cout << "test_divide OK\n";
}
void test_mix(){
	int err = 0;
	Calculator c("-2 + 3*-4 + 5 -6/2");
	int res = c.Calc(err);
	assert(res == -12);
	std::cout << "test_mix OK\n";
}
int main(int argc, char* const argv[]){

	test_plus();
	test_plus_minus();
	test_minus_minus();
	test_mult();
	test_divide();
	test_mix();
	return 0;
}
