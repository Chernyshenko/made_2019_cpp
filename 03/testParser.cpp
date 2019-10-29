#include "parser.hpp"
#include <cassert>

std::vector<std::string> testS;
long testN;
int indexS;

void StartParsing(){
    std::cout << "Test Parser Starts\n\n";
}
void FinishParsing(){
    std::cout << "\nTest Parser Finished\n";
}
void StringParsed(const std::string& s){
    assert(s == testS[indexS++]);
    std::cout << "Correct string parsed: " << s << std::endl;
}
void EmptyStringParsed(const std::string& s){
    std::cout << "Wrong string parsed: " << s << std::endl;
    assert(true);
}
void NoNumberParsed(long long n){
    std::cout << "Wrong Number Parsed: " << n << std::endl;
    assert(true);
}

void NumberParsed(long long n){
    assert(n == testN);
    std::cout << "NumberParsed done: " << n << std::endl;
}
void testString(){
    std::string str = " asd \n\n d 12\t 12e2e32 \t  \n";
    testS.clear();
    testS.push_back("asd");
    testS.push_back("d");
    testS.push_back("12e2e32");
    testN = 12;
    indexS = 0;

    Parser p(str, StringParsed, NumberParsed, StartParsing, FinishParsing);
}
void testEmpty(){
    std::string str1 = "  \n \t \t\t \n\n   ";
    std::string str2 = "";
    Parser p1(str1, EmptyStringParsed, NoNumberParsed);
    Parser p2(str2, EmptyStringParsed, NoNumberParsed);
}
int main(){

    testString();
    testEmpty();
  
    return 0;
}