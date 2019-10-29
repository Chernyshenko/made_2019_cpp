#pragma once
#include <string>
#include <iostream>
#include <vector>
class Parser
{
private:
    using Started = void (*)();
    using Finished = void (*)();
    using StringParsed = void (*)(const std::string& token);
    using NumberParsed = void (*)(long long token);
public:
    Parser(const std::string& str, StringParsed callbackStringParsed, NumberParsed callbackNumberParsed,
    	Started callbackStarted = nullptr, Finished callbackFinished = nullptr);
    ~Parser(){}
};