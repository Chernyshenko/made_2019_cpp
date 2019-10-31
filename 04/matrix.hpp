#pragma once
#include <vector>
#include <assert.h>
#include <stdexcept> 
#include <iostream>
class Row{
private:
    std::vector<int> data;
public:
    Row(size_t cols) { data.resize(cols); }
    ~Row(){}; 
    int& operator[](const int i) {
        if (i >= data.size()) 
            throw std::out_of_range("wrong column");
        return data[i];
    }
    const int& operator[](const int i) const {
        if (i >= data.size()) 
            throw std::out_of_range("wrong column");
        return data[i];
    }
    Row& operator*=(const int k){
        for (auto& i : data){
            i *= k;
        }
        return  *this;
    }
    bool operator==(const Row& row) const;
    bool operator!=(const Row& row) const {
        return !(*this == row);
    }

};


class Matrix
{
private:
    size_t cols;
    std::vector<Row> Rows;
public:
    Matrix(const size_t rows_, const size_t cols_) : 
        cols(cols_)
    {
        for (int i = 0; i < rows_; i++){
            Rows.push_back(Row(cols));
        }
    }
    ~Matrix() {};
    size_t getRows()    const { return Rows.size(); } 
    size_t getColumns() const { return cols; }
    const Row& operator[](const int i) const { 
        if (i >= Rows.size()) throw std::out_of_range("wrong row");
        return Rows[i];
    }
    Row& operator[](const int i) { 
        if (i >= Rows.size()) throw std::out_of_range("wrong row");
        return Rows[i];
    }
    Matrix& operator*=(const int k){
        for (auto& r : Rows){
            r *= k;
        }
        return *this;
    }
    bool operator==(const Matrix& m) const;
    bool operator!=(const Matrix& m) const{
        return !(*this == m);
    }
};