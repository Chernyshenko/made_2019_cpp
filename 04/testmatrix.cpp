#include "matrix.hpp"
using namespace std;

void test_sizes(){

    const size_t rows = 5;
    const size_t cols = 3;
    Matrix m(rows, cols);

    assert(m.getRows() == 5);
    assert(m.getColumns() == 3);
    cout << "test_sizes done\n";
}
void test_element(){
    const size_t rows = 5;
    const size_t cols = 3;
    Matrix m(rows, cols); 
    m[1][2] = 5;
    assert(m[1][2] == 5);

    const Matrix mc(rows, cols); 
    assert (mc[1][2] == 0);
    cout << "test_element done\n";
}
void test_equal_matrices(){
    const size_t rows = 5;
    const size_t cols = 3;
    Matrix m1(rows, cols); 
    m1[1][2] = 5;
    m1[2][1] = 7;

    Matrix m2(rows, cols); 
    m2[1][2] = 5;
    m2[2][1] = 7;

    assert(m1 == m1);
    assert(m1 == m2);
    m2[0][0] = 1;
    assert(m1 != m2);
    cout << "test_equal_matrices done\n";
}
void test_multiply_by_number(){
    const size_t rows = 4;
    const size_t cols = 3;
    Matrix m(rows, cols); 
    m[1][2] = 5;
    m[2][1] = 7;
    m *= 10;

    assert (m[1][2] == 50);
    assert (m[2][1] == 70);
    cout << "test_multiply_by_number done\n";
}
int main(){
    
    test_sizes();
    test_element();
    test_equal_matrices();
    test_multiply_by_number();
    return 0;
}