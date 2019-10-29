#include<stdio.h>
#include"LinearAllocator.hpp"
#include <cassert>


void test_allocate_more(){
    printf("Test to allocate more then maxSize\n");
    int maxSize = 1000000;
    int n = maxSize + 1;
    LinearAllocator la(maxSize);
    char* A = la.alloc(n);
    assert(A == nullptr);
    printf("Done\n");
}
void test_allocate_less(){
    printf("Test to allocate less then maxSize\n");
    int maxSize = 1000000;
    int n = maxSize - 1;
    LinearAllocator la(maxSize);
    char* A = la.alloc(n);
    assert(A != nullptr);
    printf("Done\n");
}
void test_allocate_three_times(){
    printf("Test to allocate 3 times\n");
    int maxSize = 1000000;
    int n = maxSize / 2;
    LinearAllocator la(maxSize);
    char* A = la.alloc(n);
    char* B = la.alloc(n);
    char* C = la.alloc(n);
    assert(A != nullptr);
    assert(B != nullptr);
    assert(C == nullptr);
    printf("Done\n");
}
void test_reset(){
    printf("Test reset\n");
    int maxSize = 1000000;
    int n = maxSize / 2;
    LinearAllocator la(maxSize);
    char* A = la.alloc(n);
    char* B = la.alloc(n);
    assert(A != nullptr);
    assert(B != nullptr);
    
    la.reset();
    char* C = la.alloc(n);
    assert(C != nullptr);
    printf("Done\n");
}

int main(){
    test_allocate_more();
    test_allocate_less();
    test_allocate_three_times();
    test_reset();
    return 0;
}