
#include "parser.hpp"

bool CheckNumber(const std::string& str){
    std::string nums = "1234567890";
    return (str.find_first_not_of(nums) == std::string::npos);
}

Parser::Parser(const std::string& str, StringParsed callbackStringParsed, NumberParsed callbackNumberParsed,
    Started callbackStart, Finished callbackFinished){
    if (callbackStart) callbackStart();
    std::string delims = " \t\n";
   
    int cur = -1;
    int prev = 0;
    int n = str.size();
    while (cur != n) {
        prev = str.find_first_not_of(delims, cur + 1);
        if (prev == std::string::npos) break;
        
        cur = str.find_first_of(delims, prev);
        if (cur == std::string::npos) cur = n;
        std::string s = str.substr(prev, cur - prev);

        if (CheckNumber(s)){
            long long num = stoll(s);
            if (callbackNumberParsed) callbackNumberParsed(num);
        } 
        else if (callbackStringParsed){
            callbackStringParsed(s);
        } 

    }
    if (callbackFinished) callbackFinished();
}
