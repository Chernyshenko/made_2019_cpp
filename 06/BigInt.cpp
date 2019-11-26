#include "BigInt.hpp"

int IntFromChar(char c){
int res = c - '0';
return res;
}

void BigInt::InitZero(){
	sign = 0;
	len = 1;
	data = new char[len];
	data[0] = '0';
}
void BigInt::InitFromChar(const char* s, size_t n, bool rev){
    len = n;

    if (n == 1 && s[0] == '0') InitZero();
    if (s[0] == '-') {
        sign = -1;
        len--;
    }
    else{
        sign = 1;
    }
    char* ptr = new char[len];
    if (data != nullptr) delete[] data;
    data = ptr;
    if (s[0] == '-') {
        strcpy(data, s + 1);
    }
    else{
        strcpy(data, s);
    }
    if (rev) std::reverse(data, data + len);   
}
void BigInt::InitFromInt(int k){
    if (k == 0) return InitZero();
    std::stringstream s;
    if (k < 0) {
    	s << '-';
    	k = -k;
    }
    int n = 0;
    while (k != 0){
        s << k % 10;
        k /= 10;
        n++;
    }
    const std::string& st(s.str());
    InitFromChar(st.c_str(), st.size(), false);
}
 bool BigInt::absLess(const BigInt& r) const{
    if (len > r.len) return false;
    else if (len < r.len) return true;
    for(int i = len -1; i >= 0; i--){
        if (data[i] < r.data[i]) return true;
        else if (data[i] > r.data[i]) return false;
    }
    return false;
}
bool BigInt::absLessOrEqual(const BigInt& r) const{
    if (len > r.len) return false;
    else if (len < r.len) return true;
    for(int i = len -1; i >= 0; i--){
        if (data[i] < r.data[i]) return true;
        else if (data[i] > r.data[i]) return false;
    }
    return true;
}
BigInt BigInt::Minus(const BigInt& r, int sign_) const{
    std::stringstream s;
    if (sign_ < 0) s << '-';
    int ad = 0;
    for(auto i = 0; i < r.len; i++){
        int dif = IntFromChar(data[i]) - IntFromChar(r.data[i]) - ad;
        if (dif < 0)
            ad = 1;
        else 
            ad = 0;

        s << (dif + 10) % 10;
    }
    for (auto i = r.len; i < len; i++){
        int dif = IntFromChar(data[i]) - ad;
        if (dif < 0)
            ad = 1;
        else 
            ad = 0;

        s << (dif + 10) % 10;
    }
    std::string st(s.str());
    int last_zeros = 0;
    int l = st.size();
    while(st[l - 1 - last_zeros++] == '0') st.pop_back();
    if (st.empty()){
        st.push_back('0');
    }
    if (st[0] == '-' && st.size() ==1)
    {
        st[0] = '0';
    }
    return BigInt(st, false);
}
BigInt BigInt::Plus(const BigInt& r, int sign_) const{
    size_t minLen = std::min(len, r.len);
    size_t maxLen = std::max(len, r.len);
    std::stringstream s;
    int ad = 0;

    if (sign_ < 0) s << '-';
    for (auto i = 0; i < minLen; i++){
        int sum = ad + IntFromChar(data[i]) + IntFromChar(r.data[i]);
        s << sum % 10;
        if (sum > 9) ad = 1;
        else ad = 0;
    }
    const BigInt& maxB = len >= r.len ? *this : r;

    for (auto i = minLen; i < maxLen; i++){
        int sum = ad + IntFromChar(maxB.data[i]);
        s << sum % 10;
        if (sum > 9) ad = 1;
        else ad = 0;
    }
    if (ad == 1) s << ad;

    const std::string& st(s.str());
    return BigInt(st, false);
}


BigInt& BigInt::operator=(const BigInt& c){
    if (this == &c)
    return *this;
    char* ptr = new char[c.len];
    delete[] data;
    data = ptr;
    len = c.len;
    sign = c.sign;
    std::copy(c.data, c.data + len, data);
    return *this;
}

BigInt& BigInt::operator=(int k){
    InitFromInt(k);
    return *this;
}

BigInt BigInt::operator -() const{
    BigInt res(*this);
    res.sign *= -1;
    return res;
}

bool BigInt::operator<(const BigInt& r) const{
    if (sign < 0){
        if (r.sign >= 0) return true;
        else return r.absLess(*this);
    }
    else if (sign > 0){
        if (r.sign <= 0) return true;
        else return absLess(r);
    }
    else
        return (r.sign > 0);
}
bool BigInt::operator<=(const BigInt& r) const{
    if (sign < 0){
        if (r.sign >= 0) return true;
        else return r.absLessOrEqual(*this);
    }
    else if (sign > 0){
        if (r.sign <= 0) return true;
        else return absLessOrEqual(r);
    }
    else
        return (r.sign >= 0);
}
bool BigInt::operator>(const BigInt& r) const{
    return r < *this;
}
bool BigInt::operator>=(const BigInt& r) const{
    return r <= *this;
}
bool BigInt::operator==(const BigInt& r) const{
	if (this == &r) return true;
	if (*this < r) return false;
	if (r < *this) return false;
	return true;
}
bool BigInt::operator!=(const BigInt& r) const{
    return !(*this == r);
}
bool BigInt::operator==(int k) const{
	return *this == BigInt(k);
} 
bool BigInt::operator!=(int k) const{
    return *this != BigInt(k);
}
bool BigInt::operator<(int k) const{
    return *this < BigInt(k);
}
bool BigInt::operator<=(int k) const{
    return *this <= BigInt(k);
}
bool BigInt::operator>(int k) const{
    return *this > BigInt(k);
}
bool BigInt::operator>=(int k) const{
    return *this >= BigInt(k);
}
BigInt BigInt::operator+(const BigInt& r) const{
    if (sign == 0) return r;
    if (r.sign == 0) return *this;
    if (r.sign > 0){
        if (sign > 0) return Plus(r, 1);
        else{ // this < 0
            if (this->absLess(r)) return r.Minus(*this, 1);
            else return Minus(r, -1);
        }
    }
    else{ // r < 0
        if (sign < 0) return Plus(r, -1);
        else{
            if (this->absLess(r)) return r.Minus(*this, -1);
            else return Minus(r, +1);
        }
    }
}


BigInt BigInt::operator-(const BigInt& r) const{
    if (sign == 0) return -r;
    if (r.sign == 0) return *this;
    
    if (r.sign > 0){
        if (sign < 0) return Plus(r, -1);
        else{ // this > 0
            if (this->absLess(r)) return r.Minus(*this, -1);
            else return Minus(r, +1);
        }
    }
    else{ // r < 0
        if (sign > 0) return Plus(r, +1);
        else{
            if (this->absLess(r)) return r.Minus(*this, +1);
            else return Minus(r, -1);
        }
    }
}

void BigInt::Print() const{
    if (sign < 0) std::cout << '-';
    for(int i = len - 1; i >= 0; i--)
        std::cout << data[i];

    std::cout << std::endl;
}
void BigInt::Print(std::stringstream& s) const{
	if (sign < 0) s << '-';
	for(int i = len - 1; i >= 0; i--)
        s << data[i];
}
