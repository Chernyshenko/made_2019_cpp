#include <cassert>

#include "BigInt.hpp"

void test_create_from_string(){
    BigInt e("1000");
    std::stringstream s;
    e.Print(s);
    assert(s.str() == "1000");

    BigInt g("-2000");
    std::stringstream sg;
    sg << g;
    assert(sg.str() == "-2000");
    std::cout << "test_create_from_string OK\n";
}
void test_create_from_int(){
    BigInt e = 1234;
    std::stringstream s;
    e.Print(s);
    assert(s.str() == "1234");

    BigInt g = -987;
    std::stringstream sg;
    sg << g;
    assert(sg.str() == "-987");
    std::cout << "test_create_from_int OK\n";
}
void test_copy_constructor(){
    BigInt a = -12345;
    BigInt e = a;
    std::stringstream s;
    e.Print(s);
    assert(s.str() == "-12345");
    std::cout << "test_copy_constructor OK\n";
}
void test_sum(){
    BigInt a("-100");
    BigInt b = 150;
    BigInt c = a + b + 10;

    std::stringstream s;
    s << c;
    assert(s.str() == "60");
    std::cout << "test_sum OK\n";
}

void test_dif(){
    BigInt a = 100;
    BigInt b = 98;
    BigInt d = 198;
    BigInt c = a - b - 1;
    assert (c == 1);
    assert (a - d == -b);

    std::cout << "test_dif OK\n";
}
void test_compare(){
    BigInt a = 10;
    BigInt b = -11;
    BigInt d = 18;
    BigInt c = 10;
    assert (c == a);
    assert (c <= a);
    assert (c >= a);
    assert (b < d);
    assert (d > a);
    assert (a != d);
    assert (a != 100);
    assert (d > 15);
    assert (b < -10);
    assert (c <= 10);
    assert (c >= 9);

    std::cout << "test_compare OK\n";
}
void test_big(){
    BigInt a("1111111111111111111111111"); //len 25
    BigInt b("3333333333333333333333333");
    BigInt c = a + b;
    BigInt d("4444444444444444444444444");
    assert (c == d);
    assert (a - d == -b);
    std::cout << "test_big OK\n";
}
int main(){

    test_create_from_string();
    test_create_from_int();
    test_copy_constructor();
    test_sum();
    test_dif();
    test_compare();
    test_big();
    
    return 0;
}


