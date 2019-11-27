#include "format.hpp"

using std::string;
using std::stringstream;
using std::vector;

int IntFromChar(char c){
    return c - '0';
}
int IntFromChar(char* c, int n){
    int res = 0;
    int d = 1;
    for(int i = n - 1; i >= 0; i--){
        res += d * IntFromChar(c[i]);
        d *= 10;
    }
    return res;
}
bool IsNum(char c){
    int n = IntFromChar(c);
    if (n >= 0 && n <= 9) return true;
    return false;
}



