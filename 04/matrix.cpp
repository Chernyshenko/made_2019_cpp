#include "matrix.hpp"

bool Row::operator==(const Row& row) const {
    if (this == &row) return true;
    int size = data.size();
    if (row.data.size() != size) return false;
    for (size_t i = 0; i < size; i++){
        if (data[i] != row.data[i]) return false; 
    }
    return true;
}

bool Matrix::operator==(const Matrix& m) const{
    if (this == &m) return true;
    int trSize = Rows.size();
    int mrSize = m.getRows();
    if (trSize != mrSize) return false;
    for (int i = 0; i < trSize; i++){
        if (m[i] != Rows[i]) return false;
    }
    return true;
}
