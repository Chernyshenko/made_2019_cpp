/*Написать свой аллокатор со стратегией линейного выделения памяти со следующим интерфейсом:
Аллокатор при создании аллоцирует указанный размер, 
после чего при вызове alloc возвращает указатель на блок запрошенного размера или nullptr, если места недостаточно. 
После вызова reset аллокатор позволяет использовать свою память снова.
*/
#include<stdio.h>
#include"LinearAllocator.hpp"


int main(){
    int n = 150;
    int maxSize = 1000;
    LinearAllocator la(maxSize);
    la.alloc(n);
    printf("Exit\n");
    return 0;
}