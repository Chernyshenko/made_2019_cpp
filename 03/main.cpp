/*

Написать библиотеку-парсер строк состоящих из следующих токенов:

строка
число
Число состоит из символов от 0 до 9, строка - все остальные символы. 
Токены разделены пробелами, символами табуляции и первода строки.

Пользователь библиотеки должен иметь возможность зарегистрировать колбек-функцию вызываемую каждый раз, 
когда найден токен, функция получает токен. 
Должно быть возможно зарегистрировать свой обработчик под каждый тип токена. 
Также должны быть колбеки вызываемые перед началом парсинга и по его окончанию.

*/

#include "parser.hpp"
#include <iostream>
void StartParsing(){
    std::cout << "Parsing Starts\n";
}
void FinishParsing(){
    std::cout << "Parsing Finished\n";
}
void StringParsed(std::string& s){
    std::cout << "string " << s << " parsed\n";
}
void NumberParsed(long long n){
    std::cout << "number " << n << " parsed\n";
}
int main(){
    std::string str = " asd d 12 12e2e32 \t  \n";
    Parser p(str, StartParsing, FinishParsing, StringParsed, NumberParsed);
    return 0;
}