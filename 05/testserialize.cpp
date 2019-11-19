#include <iostream>
#include <sstream>
#include <cassert>

#include "serializer.hpp"
#include "data.hpp"

using namespace std;
void test_serializer(){
    Data x { 1, true, 2 };
    std::stringstream streamx;

    Serializer serializerx(streamx);
    serializerx.save(x);

    assert(streamx.str() == "1 true 2 ");

    Data y { 0, false, 20 };
    std::stringstream streamy;

    Serializer serializery(streamy);
    serializery.save(y);

    assert(streamy.str() == "0 false 20 ");
    std::cout << "test_serializer done\n";
}
void test_deserializer(){
    std::stringstream stream;
    stream << "1 true 20";
    Deserializer deserializer(stream);

    Data y { 0, false, 0 };
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);
    assert(y.a == 1);
    assert(y.a == true);
    assert(y.c == 20);
    std::cout << "test_deserializer done\n";
}

int main(){
    
    test_serializer();
    test_deserializer();
    return 0;
}