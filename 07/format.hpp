#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

int IntFromChar(const char* c, int n);
bool IsNum(char c);

std::string format_argv(const std::string& s, std::vector<std::string>& argv);
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


template < class T, class... Args>
std::string format(const std::string& s, T&& val, Args&&... args){
    std::vector<std::string> argv;
    make_arg_string(argv, std::forward<T>(val), std::forward<Args>(args)...);    
    return format_argv(std::move(s), argv);
}
