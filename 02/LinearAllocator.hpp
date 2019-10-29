#include<stdlib.h>
#include <iostream>
class LinearAllocator
{
private:
    size_t shift;
    size_t maxSize;
    char *buffer;
public:
    LinearAllocator(size_t maxSize_)
    : maxSize(maxSize_)
    , shift(0)
    {
        buffer = (char*) malloc(maxSize * sizeof(char));
        if (!buffer) throw std::runtime_error("Cannot allocate memory");
    }
    ~LinearAllocator(){
        if (buffer) free(buffer);
    }
    char* alloc(size_t size){
        if (size < 0) return nullptr;
        if (size > maxSize - shift) return nullptr;
        int shift_prev = shift;
        shift += size;
        return buffer + shift_prev;
    }
    void reset(){shift = 0;}
};
