#pragma once
#include <string>
#include <iostream>
#include <vector>
class Parser
{
private:
    using Started = void (*)();
    using Finished = void (*)();
    using StringParsed = void (*)(std::string& token);
    using NumberParsed = void (*)(long long token);
public:
    Parser(const std::string& str, Started callbackStarted, Finished callbackFinished,
            StringParsed callbackStringParsed, NumberParsed callbackNumberParsed);
    ~Parser(){}
};