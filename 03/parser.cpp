
#include "parser.hpp"

bool CheckNumber(const std::string& str){
    std::string nums = "1234567890";
    if (str.find_first_not_of(nums) == std::string::npos)
        return true;
    return false;
}

Parser::Parser(const std::string& str,
    Started callbackStart, Finished callbackFinished, StringParsed callbackStringParsed, NumberParsed callbackNumberParsed){
    callbackStart();
    std::string delims = " \t\n";
   
    int prev = str.find_first_not_of(delims);
    int cur = str.find_first_of(delims, prev);
    while (cur != std::string::npos) {
        std::string s = str.substr(prev, cur - prev);

        if (CheckNumber(s)){
            long long num = stoll(s);
            callbackNumberParsed(num);
        } 
        else {
            callbackStringParsed(s);
        }
        prev = str.find_first_not_of(delims, cur + 1);
        cur = str.find_first_of(delims, prev);

    }
    if (prev != std::string::npos ){
        std::string s = str.substr(prev, str.size()- prev);
        if (CheckNumber(s)){
            long long num = stoll(s);
            callbackNumberParsed(num);
        } 
        else {
            callbackStringParsed(s);
        }
    }
    callbackFinished();
}
