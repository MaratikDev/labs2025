#ifndef VECTOR_H
#define VECTOR_H
#include "exceptions.h"
#include <iostream>
#include <initializer_list>
#include "Iterator.h"
#include "StaticIterator.h"
#include <fstream>
template <typename T>
class Vector {
private:
    T *arr;
    int size;

public:

    Vector(int length);
    explicit Vector(std::initializer_list<T>& lst);
    Vector<T>(Vector<T>&& otherVect);
    Vector(const Vector<T>& vect);
    ~Vector();

    int getLength() const;
    void setElem(int index, const T& elem);

    T& getElem(int index) const;
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
    StaticIterator<T> beginStatic();
    StaticIterator<T> endStatic();
    Iterator<T> end();
    void generateGraphViz(const std::string& filename);
    int showGraph(const std::string& filename);
};
#endif // VECTOR_H
