#include "format.hpp"

using std::string;
using std::stringstream;
using std::vector;

int IntFromChar(char c){
    return c - '0';
}

int IntFromChar(const char* c, int n){
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

std::string format_argv(const std::string& s, std::vector<std::string>& argv){
       
    std::stringstream res;
    std::stringstream stream;
    stream << s;
    const char left = '{', right = '}';
    char c;
    int argc = argv.size();
    for (auto i = 0; i < s.size(); i++){
        if (s[i] == left){
            i++;
            int j = 0;
            while(IsNum(s[i+j])) j++;
            int argi = IntFromChar(s.c_str() + i, j);
            if (argi < 0 || argi >= argc) throw std::runtime_error("Cannot read arg index");
            res << argv[argi];
            i += j;
            if (s[i] != right) throw std::runtime_error("Not }");
        }
        else if (s[i] == right) throw std::runtime_error("Symbol } is out of context");
        else res << s[i];
    }
    return res.str();
}