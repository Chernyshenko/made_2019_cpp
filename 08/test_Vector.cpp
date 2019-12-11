#include <iostream>
#include <assert.h>
#include "Vector.hpp"
using std::endl;
using std::cout;

void test_operator(){
    Vector<int> v(10);
    v[1] = 2;
    assert (v[1] == 2);
    cout << "test_operator[] OK\n";
}
void test_size(){
    Vector<int> v(10);
    assert(v.size() == 10);
    cout << "test_size OK\n";
}
void test_resize(){
    Vector<int> v(10);
    assert(v.size() == 10);
    
    v.resize(20);
    assert(v.size() == 20);

    v.resize(5);
    assert(v.size() == 5);
    cout << "test_resize OK\n";
}
void test_reserve(){
    Vector<int> v;
    v.reserve(100);

    assert(v.capacity() == 100);
    assert(v.size() == 0);

    v.reserve(20);

    assert(v.capacity() == 100);
    
    cout << "test_reserve OK\n";
}
void test_push(){
    Vector<int> v;
    for (int i = 0; i < 10; i++)
        v.push_back(i);

    for (int i = 0; i < 10; i++)
        assert(v[i] == i);

    assert(v.size() == 10);

    cout << "test_push OK\n";
}
void test_pop(){
    Vector<int> v;
    for (int i = 0; i < 10; i++)
        v.push_back(i);

    for (int i = 0; i < 9; i++)
        v.pop_back();

    assert(v.size() == 1);
    assert(v[0] == 0);

    cout << "test_pop OK\n";
}
void test_empty(){
    Vector<int> v;
    for (int i = 0; i < 10; i++)
        v.push_back(i);

    for (int i = 0; i < 10; i++)
        v.pop_back();

    assert(v.empty());

    cout << "test_empty OK\n";
}
void test_clear(){
    Vector<int> v;
    for (int i = 0; i < 10; i++)
        v.push_back(i);

    v.clear();
    assert(v.empty());

    cout << "test_clear OK\n";
}
void test_iterators(){
    Vector<int> v;
    for (int i = 0; i < 10; i++)
        v.push_back(i);

    int sum = 0;
    for(Vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        sum += *it;
    
    assert(sum == 45);
    
    int sum2 = 0;
    for(Vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
        sum2 += *it;
    
    assert(sum2 == 45);
    
    cout << "test_iterators OK\n";
}
int main(){
	
    test_operator();
    test_size();
    test_resize();
    test_reserve();
    test_push();
    test_pop();
    test_empty();
    test_clear();
    test_iterators();
    return 0;
}