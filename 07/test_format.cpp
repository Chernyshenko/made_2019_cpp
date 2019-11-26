#include <assert.h>
#include "format.hpp"

using std::cout;
using std::endl;

void test_2arg(){
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2"); 
    cout << "test_2arg OK\n"; 
}
void test_12arg(){
    auto text2 = format("{0}+{1}+{2}+{3}+{4}+{5}+{6}+{7}+{8}+{9}+{10}={11}",
                          "10", 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 165);

    assert(text2 == "10+11+12+13+14+15+16+17+18+19+20=165");
    cout << "test_12arg OK\n"; 
}

void test_throw_runtime_error1(){
    try{
        auto text = format("{1}}+{1} = {0}", 2, "one");
    }
    catch(const std::runtime_error& error){
        std::string s = error.what();
        assert (s == "Symbol } is out of context");
    }
    cout << "test_throw_runtime_error1 OK\n"; 
}
void test_throw_runtime_error2(){
    try{
        auto text = format("{1]+{1} = {0}", 2, "one");
    }
    catch(const std::runtime_error& error){
        std::string s = error.what();
        assert (s == "Not }");
    }
    cout << "test_throw_runtime_error2 OK\n"; 
}
void test_throw_runtime_error_wrong_arg(){
    try{
        auto text = format("{2}+{1} = {0}", 2, "one");
    }
    catch(const std::runtime_error& error){
        std::string s = error.what();
        assert (s == "Cannot read arg index" );
    }
    cout << "test_throw_runtime_error_wrong_arg OK\n"; 
}
int main(int argc, char const *argv[])
{
    try{
        test_2arg();
        test_12arg();
        test_throw_runtime_error1();
        test_throw_runtime_error2();
        test_throw_runtime_error_wrong_arg();
    }
    catch(const std::runtime_error& error){
        cout << "Catched runtime_error: " << error.what() << endl; 
    }
    return 0;
}