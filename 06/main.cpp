#include "BigInt.hpp"

int main(){
    BigInt a = 1;
    BigInt b = a;
    BigInt c = a + b + 2;
    c.Print();
    
    return 0;
}


