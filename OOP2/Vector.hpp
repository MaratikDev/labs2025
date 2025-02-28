#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "Vector.h"

template<typename T>
Iterator<T> Vector<T>::begin(){
    return Iterator<T>(*this);
}
template<typename T>
Iterator<T> Vector<T>::end(){
    Iterator<T> iter(*this);
    while(!iter.is_end()){
        iter.next();
    }
    return iter;
}

template<typename T>
Vector<T>::Vector(int length) {
    this->size = length;
    this->arr = new T[size];
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T>& lst) {
    this->arr = new T[lst.size()];
    this->size = lst.size();
    int i = 0;
    for (T elem : lst) {
        arr[i++] = elem;
    }
}

template<typename T>
Vector<T>::Vector(const Vector<T>& vect) {
    this->size = vect.size;
    this->arr = new T[size];
    for (int i = 0; i < size; i++) {
        this->arr[i] = vect.arr[i];
    }
}

template<typename T>
Vector<T>::~Vector() {
    delete[] arr;
}

template<typename T>
Vector<T>& Vector<T> :: operator = (const Vector<T>& lst) {
    if (this == &lst) {
        return *this;
    }
    delete[] arr;
    this->size = lst.size;
    this->arr = new T[this->size];
    for (int i = 0; i < this->size; i++) {
        this->arr[i] = lst.arr[i];
    }
    return *this;
}

template<typename T>
int Vector<T>::getLength() {
    return this->size;
}

template<typename T>
void Vector<T>::setElem(int index, const T& elem) {
    if(index >= this->get_length())
        throw "out of range"; // потм сделать exception
    else{
        arr[index] = elem;
    }
}

template<typename T>
T& Vector<T>::getElem(int index) {
    if(index >= this->get_length())
        throw "out of range"; // потм сделать exception
    else{
        return arr[index];
    }
}

template<typename T>
T* Vector<T>::toArray() {
    T* array = new T[this->size];
    for (int i = 0; i < this->size; i++) {
        array[i] = this->arr[i];
    }
    return array;
}

template<typename T>
T& Vector<T>::operator[](int index) {
    if(index >= this->get_length())
        throw "out of range"; // потм сделать exception
    else{
        return arr[index];
    }
}

template<typename T>
Vector<T>& Vector<T> :: operator += (const Vector<T>& vect)
{
    int tempSize = std::max(vect.size, this->size);
    T* tempArr = new T[tempSize];
    int i = 0;

    if (this->size >= vect.size) {
        for (i; i < vect.size; i++) {
            tempArr[i] = this->arr[i] + vect.arr[i];
        }
        for (i; i < this->size; i++) {
            tempArr[i] = this->arr[i] ;
        }

    }
    else {
        for (i; i < this->size; i++) {
            tempArr[i] = this->arr[i] + vect.arr[i];
        }
        for (i; i < vect.size; i++) {
            tempArr[i] = vect.arr[i];
        }
    }
    this->size = tempSize;
    this->arr = tempArr;
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& vect)
{
    int tempSize = std::max(vect.size, this->size);
    T* tempArr = new T[tempSize];
    int i = 0;

    if (this->size >= vect.size) {
        for (i; i < vect.size; i++) {
            tempArr[i] = this->arr[i] - vect.arr[i];
        }
        for (i; i < this->size; i++) {
            tempArr[i] = this->arr[i] ;
        }

    }
    else {
        for (i; i < this->size; i++) {
            tempArr[i] = this->arr[i] - vect.arr[i];
        }
        for (i; i < vect.size; i++) {
            tempArr[i] = 0-vect.arr[i];
        }
    }


    this->size = tempSize;
    this->arr = tempArr;
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator*=(const T& val)
{
    int i = 0;
    for (i; i < this->size; i++) {
        this->arr[i] = this->arr[i] * val;
    }

    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator/=(const T& val)
{
    int i = 0;
    for (i; i < this->size; i++) {
        this->arr[i] = this->arr[i] / val;
    }

    return *this;
}
template<typename T>
std::ostream& operator << (std::ostream& os, const Vector<T>& lst){
    os << "mat vect: ";
    for (int i = 0; i < lst.size; i++) {
        os << lst.arr[i] << " ";
    }
    return os;
}
template<typename T>
Vector<T> operator +(const Vector<T>& v1, const Vector<T>& v2){
    int tempSize = std::max(v1.size, v2.size);
    Vector<T> tempVec (tempSize);
    int i = 0;
    if (v1.size >= v2.size) {
        for (i; i < v2.size; i++) {
            tempVec.set_elem(i, v1.arr[i] + v2.arr[i]);
        }
        for (i; i < v1.size; i++) {
            tempVec.set_elem(i, v1.arr[i]);
        }
    }
    else {
        for (i; i < v1.size; i++) {
            tempVec.set_elem(i, v1.arr[i] + v2.arr[i]);
        }
        for (i; i < v2.size; i++) {
            tempVec.set_elem(i, v2.arr[i]);
        }
    }
    return tempVec;
}
template<typename T>
Vector<T> operator -(const Vector<T>& v1, const Vector<T>& v2){
    int tempSize = std::max(v1.size, v2.size);
    Vector<T> tempVec(tempSize);
    int i = 0;
    if (v1.size >= v2.size) {
        for (i; i < v2.size; i++) {
            tempVec.set_elem(i, v1.arr[i] - v2.arr[i]);
        }
        for (i; i < v1.size; i++) {
            tempVec.set_elem(i, v1.arr[i]);
        }
    }
    else {
        for (i; i < v1.size; i++) {
            tempVec.set_elem(i, v1.arr[i] - v2.arr[i]);
        }
        for (i; i < v2.size; i++) {
            tempVec.set_elem(i, 0-v2.arr[i]);
        }
    }
    return tempVec;
}
template<typename T>
Vector<T> operator *(const Vector<T>& v1, const T& val){
    Vector<T> tempVec(v1.size);
    for (int i = 0; i < v1.size; i++) {
        tempVec.set_elem(i, v1.arr[i] * val);
    }
    return tempVec;
}
template<typename T>
Vector<T> operator /(const Vector<T>& v1, const T& val){
    Vector<T> tempVec(v1.size);
    for (int i = 0; i < v1.size; i++) {
        tempVec.set_elem(i, v1.arr[i] / val);
    }
    return tempVec;
}
#endif // VECTOR_HPP
