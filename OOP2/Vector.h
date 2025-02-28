#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <initializer_list>
#include "Iterator.h"

template <typename T>
class Vector {
private:
    T *arr;
    int size;

public:

    Vector(int length);
    explicit Vector(std::initializer_list<T>& lst);
    Vector(const Vector<T>& vect);
    ~Vector();

    int getLength();
    void setElem(int index, const T& elem);

    T& getElem(int index);
    T* toArray();
    T& operator[](int index);

    Vector<T>& operator = (const Vector<T>& lst);
    Vector<T>& operator += (const Vector<T>& vect);
    Vector<T>& operator -= (const Vector<T>& vect);
    Vector<T>& operator *= (const T& val);
    Vector<T>& operator /= (const T& val);

    friend std::ostream& operator << (std::ostream& os, const Vector<T>& lst);
    friend Vector<T> operator +(const Vector<T>& v1, const Vector<T>& v2);
    friend Vector<T> operator -(const Vector<T>& v1, const Vector<T>& v2);
    friend Vector<T> operator *(const Vector<T>& v1, const T& val);
    friend Vector<T> operator /(const Vector<T>& v1, const T& val);
    Iterator<T> begin();
    Iterator<T> end();
};
#endif // VECTOR_H
