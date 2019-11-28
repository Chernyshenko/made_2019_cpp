#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

int IntFromChar(const char* c, int n);
bool IsNum(char c);
template <class String = std::string>
std::string format_argv(String&& s, std::vector<std::string>& argv){
       
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
template <class T>
void make_arg_string(std::vector<std::string>& argv, T&& val){
    std::stringstream stream;
    stream << val;
    argv.push_back(stream.str());
}
template <class T, class... Args>
void make_arg_string(std::vector<std::string>& argv, T&& val, Args&&... args){
    make_arg_string(argv, std::forward<T>(val));
    make_arg_string(argv, std::forward<Args>(args)...);
}


template <class String = std::string, class T, class... Args>
std::string format(String&& s, T&& val, Args&&... args){
    std::vector<std::string> argv;
    make_arg_string(argv, std::forward<T>(val), std::forward<Args>(args)...);    
    return format_argv(std::forward<std::string>(s), argv);
}
/*
template <class T, class... Args>
std::string format(std::string& s, T&& val, Args&&... args){
    std::vector<std::string> argv;
    make_arg_string(argv, std::forward<T>(val), std::forward<Args>(args)...);    
    return format_argv(std::forward<std::string>(s), argv);
}*/