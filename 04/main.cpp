/*
Нужно написать класс-матрицу, тип элементов int. 
В конструкторе задается количество рядов и строк. 
Поддерживаются оперции: получить количество строк(rows)/столбцов(columns), 
получить конкретный элемент, умножить на число(*=), сравнение на равенство/неравенство. 
В случае ошибки выхода за границы бросать исключение:
throw std::out_of_range("")
*/
#include "matrix.hpp"
using namespace std;

int main(){
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);

    assert(m.getRows() == 5);
    assert(m.getColumns() == 3);

    m[1][2] = 5; // строка 1, колонка 2
    double x = m[4][1];


    m *= 3; // умножение на число
    cout << x << endl;
    cout << m[1][2] << endl;
    Matrix m1(rows, cols);
    m1[1][2] = 15;

    if (m1 == m)
    {
        cout << "equal matrices\n";
    }
    return 0;
}