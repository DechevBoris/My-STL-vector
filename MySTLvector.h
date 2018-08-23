#pragma once
#include <iostream>
using namespace std;

template <typename T>
class MyVector
{
private:
    T* vec;
    size_t size;
    size_t capacity;

    void copy(const MyVector& other);
    void erase();
    void resize();
public:
    MyVector();
    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);
    ~MyVector();
    size_t getSize()const;
    size_t getCapacity()const;
    void print()const;
    T operator[](size_t index)const;             //Get element by index
    size_t operator[](T el)const;                //Get index by element
    MyVector& operator+(const MyVector& other); //Concatenates two vectors by sticking the 2nd to the 1st
    size_t getIndexByEl(T el)const;
    void addElAtTheBack(T el);
    void addElAtTheFront(T el);
    void addElAtIndex(T el, size_t index);
    void removeLastEl();
    void removeFirstEl();
    void removeElByIndex(size_t index);
    void clean();                                //Remove all elements
};

template <typename T>
void MyVector<T>::copy(const MyVector& other)
{
    this->vec = new T[other.capacity];
    for(size_t i = 0; i < other.size; i++)
        this->vec[i] = other.vec[i];
    this->size = other.size;
    this->capacity = other.capacity;
}

template <typename T>
void MyVector<T>::erase()
{
    delete[] this->vec;
}

template <typename T>
void MyVector<T>::resize()
{
    this->capacity *= 2;
    T* tmp = new T[this->capacity];
    for(size_t i = 0; i < this->size; i++)
        tmp[i] = this->vec[i];
    delete[] this->vec;
    this->vec = tmp;
}

template <typename T>
MyVector<T>::MyVector()
{
    this->size = 0;
    this->capacity = 4;
    this->vec = new T[this->capacity];
}

template <typename T>
MyVector<T>::MyVector(const MyVector& other)
{
    this->copy(other);
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other)
{
    if(this != &other)
    {
        this->erase();
        this->copy(other);
    }
    return *this;
}

template <typename T>
MyVector<T>::~MyVector()
{
    this->erase();
}

template <typename T>
size_t MyVector<T>::getSize()const
{
    return this->size;
}

template <typename T>
size_t MyVector<T>::getCapacity()const
{
    return this->capacity;
}

template <typename T>
void MyVector<T>::print()const
{
    for(size_t i = 0; i < this->size; i++)
        cout << this->vec[i] << endl;
}

template <typename T>
T MyVector<T>::operator[](size_t index)const
{
    if(index < 0 || index >= this->size)
        throw invalid_argument("Invalid index!");
    return this->vec[index];
}

template <typename T>
size_t MyVector<T>::operator[](T el)const
{
    for(size_t i = 0; i < this->size; i++)
        if(el == this->vec[i])
            return i;
    throw invalid_argument("No such element in the vector!");
}

template <typename T>
MyVector<T>& MyVector<T>::operator+(const MyVector& other)
{
    while(this->size + other.size >= this->capacity)
        this->resize();
    size_t tmp = this->size;
    this->size += other.size;
    for(size_t i = tmp; i < this->size; i++)
        this->vec[i] = other.vec[i - tmp];
    return *this;
}

template <typename T>
size_t MyVector<T>::getIndexByEl(T el)const
{
    for(size_t i = 0; i < this->size; i++)
        if(this->vec[i] == el)
            return i;
    throw invalid_argument("No such element!");
}

template <typename T>
void MyVector<T>::addElAtTheBack(T el)
{
    if(this->size == this->capacity)
        this->resize();
    this->vec[this->size++] = el;
}

template <typename T>
void MyVector<T>::addElAtTheFront(T el)
{
    if(this->size == this->capacity)
        this->resize();
    this->size++;
    for(size_t i = this->size - 1; i >= 1; i--)
        this->vec[i] = this->vec[i - 1];
    this->vec[0] = el;
}

template <typename T>
void MyVector<T>::addElAtIndex(T el, size_t index)
{
    if(index <= this->size)
    {
        if(this->size == this->capacity)
            this->resize();
        this->size++;
        for(size_t i = this->size - 1; i >= 1; i--)
        {
            if(index == this->size - 1)
                break;
            this->vec[i] = this->vec[i - 1];
            if(i == index + 1)
                break;
        }
        this->vec[index] = el;
    }
    else
        throw invalid_argument("Index too great!");
}

template <typename T>
void MyVector<T>::removeLastEl()
{
    if(this->size > 0)
        this->size--;
    else
        throw logic_error("The vecor is already empty!");
}

template <typename T>
void MyVector<T>::removeFirstEl()
{
    if(this->size > 0)
    {
        for(size_t i = 0; i < this->size - 1; i++)
            this->vec[i] = this->vec[i + 1];
        this->size--;
    }
    else
        throw logic_error("The vecor is already empty!");
}

template <typename T>
void MyVector<T>::removeElByIndex(size_t index)
{
    if(index < 0 || index >= this->size)
        throw invalid_argument("Invalid index!");
    else
    {
        for(size_t i = index; i < this->size - 1; i++)
            this->vec[i] = this->vec[i + 1];
        this->size--;
    }
}

template <typename T>
void MyVector<T>::clean()
{
    if(this->size > 0)
        size -= size;
    else
        throw logic_error("The vecor is already empty!");
}
