#include <iostream>

#include "calc.hpp"

int main(int argc, char* const argv[]){
	if (argc != 2){
		std::cout << "Usage: calc \"2 + 3 * 4 - -2\"" << std::endl;
		return -1;
	}
	int err = 0;
	Calculator c(argv[1]);
	int res = c.Calc(err);
	if (err){
		std::cout << "Error in input format\n";
	}
	else
		std::cout << res << std::endl;
	
	return err;
}
