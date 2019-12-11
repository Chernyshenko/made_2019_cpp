#pragma once
#include <cstring>
#include <iterator>
#include <assert.h>
template <class T>
class Allocator: public std::allocator<T>
{
public:
    using std::allocator<T>::allocator;
};

template <class T>
class Iterator
    : public std::iterator<std::forward_iterator_tag, T>
{
    T* ptr_;
public:
    using reference = T&;

    explicit Iterator(T* ptr)
        : ptr_(ptr)
    {
    }

    bool operator==(const Iterator<T>& other) const
    {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<T>& other) const
    {
        return !(*this == other);
    }

    reference operator*() const
    {
        return *ptr_;
    }

    Iterator& operator++()
    {
        ++ptr_;
        return *this;
    }

    Iterator& operator--()
    {
        --ptr_;
        return *this;
    }
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using iterator =  Iterator<T>;
    using reverse_iterator = std::reverse_iterator<Iterator<T>>;
    using size_type = size_t;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
	using allocator_type = Alloc;

    explicit Vector();
    explicit Vector(size_type count);

    Vector(size_type count, const value_type& defaultValue);
    ~Vector();

    iterator begin() noexcept {return iterator(data);}

    iterator end() noexcept {return iterator(data + size_);}

    reverse_iterator rbegin() noexcept { return reverse_iterator(end());}

    reverse_iterator rend() noexcept{ return reverse_iterator(begin());}

    void push_back(value_type&& value);
    void push_back(const value_type& value);
    void pop_back();
    

    void reserve(size_type count); // Выделяет память
    size_type capacity() const noexcept {return capacity_;}
    size_type size() const noexcept {return size_;}
    bool empty() const noexcept;

    void resize(size_type newSize); // Изменяет размер
    void resize(size_type newsize, const_reference defaultValue);

    void clear() noexcept;
    reference operator[](const size_type i) {return data[i];}

private:
    Alloc alloc_;
    T* data;
    size_type capacity_;
    size_type size_;

    void reallocate(size_type newsize);
};



template <class T, class Alloc>
void Vector<T, Alloc>:: reallocate(size_type newsize){
    T* mem = alloc_.allocate(newsize);
    if (mem){
        memmove(mem, data, size_ * sizeof(T));
        data = mem;
    }
    else{
        throw std::bad_alloc();
    }
}
template <class T, class Alloc>
Vector<T, Alloc>::Vector() : capacity_(4), size_(0){ 
    data = alloc_.allocate(capacity_);
}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(size_type count) : capacity_(count), size_(count) { 
    data = alloc_.allocate(capacity_);
}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(size_type count, const value_type& defaultValue) : capacity_(count), size_(count){
    data = alloc_.allocate(capacity_);
    for(size_type i = 0; i < size_; i++)
        data[i] = defaultValue;
}
template <class T, class Alloc>
Vector<T, Alloc>::~Vector(){
    alloc_.deallocate(data, capacity_);
}

template <class T, class Alloc>
void Vector<T, Alloc>::reserve(size_type count){
    if (count <= capacity_) return;
    capacity_ = count;
    reallocate(capacity_);
}
template <class T, class Alloc>
void Vector<T, Alloc>::resize(size_type newsize){
    if (newsize < size_){
        size_ = newsize;
    }
    else{
        if (capacity_ < newsize){
            capacity_ = newsize;
            reallocate(capacity_);
        }
        for(size_type i = size_; i < newsize; i++){
            data[i] = T();
        }   
        size_ = newsize; 
    }
}

template <class T, class Alloc>
void Vector<T, Alloc>::resize(size_type newsize, const_reference defaultValue){
    if (newsize < size_){
        size_ = newsize;
    }
    else{
        if (capacity_ < newsize){
            capacity_ = newsize;
            reallocate(capacity_);
        }
        for(size_type i = size_; i < newsize; i++){
            data[i] = defaultValue;
        }
        size_ = newsize;     
    }    

}
template <class T, class Alloc>
void Vector<T, Alloc>::push_back(value_type&& value){
    if (capacity_ < size_ + 1) {
        capacity_ *= 2;
        reallocate(capacity_);
    }
    data[size_] = value;
    size_++;   
}
template <class T, class Alloc>
void Vector<T, Alloc>::push_back(const value_type& value){
    if (capacity_ < size_ + 1) {
        capacity_ *= 2;
        reallocate(capacity_);
    }
    data[size_] = value;
    size_++;   
}

template <class T, class Alloc>
void Vector<T, Alloc>::pop_back(){
    assert (size_ > 0);
    size_--;
}
template <class T, class Alloc>
bool Vector<T, Alloc>::empty() const noexcept {
    return size_ == 0;
}
template <class T, class Alloc>
void Vector<T, Alloc>::clear() noexcept {
    size_ = 0;
}
