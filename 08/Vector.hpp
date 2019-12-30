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
    : public std::iterator<std::random_access_iterator_tag, T>
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

    Iterator& operator+=(int n)
    {
        ptr_ = ptr_ + n;
        return *this;
    }
    Iterator& operator+(int n)
    {
        T* res = ptr_ + n;
        return res;
    }
    Iterator& operator+(const Iterator<T>& other)
    {
        Iterator res(ptr_ + other.ptr_);
        return res;
    }

    Iterator& operator--()
    {
        --ptr_;
        return *this;
    }
    Iterator& operator-=(int n)
    {
        ptr_ = ptr_ - n;
        return *this;
    }
    Iterator& operator-(int n)
    {
        Iterator res(ptr_ - n);
        return res;
    }

    Iterator& operator-(const Iterator<T>& other)
    {
        Iterator res(ptr_ - other.ptr_);
        return res;
    }
    bool operator<(const Iterator<T>& other) const{
        return ptr_ < other.ptr_;
    }
    bool operator>(const Iterator<T>& other) const{
        return other.ptr_ < ptr_;
    }
    bool operator>=(const Iterator<T>& other) const{
        return !(ptr_ < other.ptr_);
    }
    bool operator<=(const Iterator<T>& other) const{
        return !(other.ptr_ < ptr_);
    }
    reference operator[](int n) const{
        return *(ptr_ + n);
    }


};

template <class T, class Alloc = Allocator<T> >
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
    T* dst = mem;
    for(T* src = data; src != data + size_; ++src, ++dst){
        alloc_.construct(dst, std::move(*src));
        alloc_.destroy(src);          
    }
    alloc_.deallocate(data, capacity_);
    data = mem;
    mem = nullptr;
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
    for(size_type i = 0; i < size_; i++){
        alloc_.construct(data + i, defaultValue);
    }
}
template <class T, class Alloc>
Vector<T, Alloc>::~Vector(){
    clear();
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
            alloc_.construct(data + i, T());
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
            alloc_.construct(data + i, defaultValue);
        }
        size_ = newsize;     
    }    

}
template <class T, class Alloc>
void Vector<T, Alloc>::push_back(value_type&& value){
    if (capacity_ == size_) {
        capacity_ *= 2;
        reallocate(capacity_);
    }
    alloc_.construct(data + size_, std::move(value));
    size_++;   
}
template <class T, class Alloc>
void Vector<T, Alloc>::push_back(const value_type& value){
    if (capacity_ == size_ ) {
        capacity_ *= 2;
        reallocate(capacity_);
    }
    alloc_.construct(data + size_, value);
    size_++;   
}

template <class T, class Alloc>
void Vector<T, Alloc>::pop_back(){
    assert (size_ > 0);
    alloc_.destroy(data + size_ - 1);
    size_--;
}
template <class T, class Alloc>
bool Vector<T, Alloc>::empty() const noexcept {
    return size_ == 0;
}
template <class T, class Alloc>
void Vector<T, Alloc>::clear() noexcept {
    for(size_type i = 0; i < size_; i++)
         alloc_.destroy(data + i);
    size_ = 0;
}
