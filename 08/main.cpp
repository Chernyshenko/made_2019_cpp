#include <iostream>
#include "Vector.hpp"
using std::endl;
using std::cout;
int main(){
	Vector<int> v(10, 2);
    std::cout << v[1] << endl; 
    cout << v.capacity() << endl;
    v.push_back(3);
    std::cout << v[10] << endl;
    cout << "capacity " <<v.capacity() << endl;
    v.resize(20);
    for (auto it = v.rbegin(); it != v.rend(); ++it)
    	cout << *it << endl;
}