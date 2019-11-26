#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
int IntFromChar(char c);

class BigInt{
private:
    size_t len;
    char* data = nullptr;
    int sign = 0;
    void InitFromChar(const char* s, size_t n, bool rev = true);
    void InitFromInt(int k);
    void InitZero();
    bool absLess(const BigInt& r) const;
    bool absLessOrEqual(const BigInt& r) const;
    BigInt Minus(const BigInt& r, int sign_) const;
    BigInt Plus(const BigInt& r, int sign_) const;
public:

    BigInt(const char* s, size_t n, bool rev = true): len(n){
        InitFromChar(s, len, rev);
    }

    BigInt() : len(0), data(nullptr) {}

    BigInt(const BigInt& copied):
        len(copied.len),
        sign(copied.sign),
        data(new char[copied.len])
    {
        std::copy(copied.data, copied.data + len, data);
    }

    BigInt(const std::string& s, bool rev = true) : BigInt(s.c_str(), s.size(), rev)
    {

    }

    BigInt(int k)
    {
        InitFromInt(k);
    }

    ~BigInt()
    {
        if (data) delete[] data;
    }
    
    void Print() const;
    void Print(std::stringstream& s) const;

    friend std::ostream &operator<<( std::ostream &output, const BigInt &b ){
        if (b.sign < 0) output << '-';
        for(int i = b.len - 1; i >= 0; i--)
            output << b.data[i];
        return output;
    }
    
    BigInt& operator=(const BigInt& c);

    BigInt& operator=(int k);
   
    BigInt operator -() const;

    bool operator<(const BigInt& r) const;
    bool operator>(const BigInt& r) const;
    bool operator<=(const BigInt& r) const;
    bool operator>=(const BigInt& r) const;
    bool operator==(const BigInt& r) const;
    bool operator!=(const BigInt& r) const;
    bool operator==(int k) const;
    bool operator!=(int k) const;
    bool operator<(int k) const;
    bool operator>(int k) const;
    bool operator<=(int k) const;
    bool operator>=(int k) const;

    BigInt operator+(const BigInt& r) const;
    
    BigInt operator-(const BigInt& r) const;

    BigInt operator+(int k) const{
        const BigInt r(k);
        return *this + r;
    }
    BigInt operator-(int k) const{
        const BigInt r(k);
        return *this - r;
    }

    BigInt& operator+=(const BigInt& r){
        *this = *this + r;
        return *this;
    }
};