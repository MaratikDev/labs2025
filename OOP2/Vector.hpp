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
    while(!iter.isEnd()){
        iter.next();
    }
    return iter;
}

template<typename T>
StaticIterator<T> Vector<T>::beginStatic(){
    return StaticIterator<T>(*this);
}
template<typename T>
StaticIterator<T> Vector<T>::endStatic(){
    StaticIterator<T> iter(*this);
    while(!iter.isEnd()){
        iter.next();
    }
    return iter;
}

template<typename T>
Vector<T>::Vector(int length) {
    if(length <= 0)
        throw OutOfIndexException("cant make vector with this size");
    this->size = length;
    this->arr = new T[size];
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T>& lst) {
    if(!lst.size())
        throw OutOfIndexException("cant make vector with this size");
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
int Vector<T>::getLength() const{
    return this->size;
}

template<typename T>
void Vector<T>::setElem(int index, const T& elem) {
    if(index >= this->getLength())
        throw OutOfIndexException("out of range");
    else{
        arr[index] = elem;
    }
}

template<typename T>
T& Vector<T>::getElem(int index) const{
    if(index >= this->getLength())
        throw OutOfIndexException("out of range");
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
    if(index >= this->getLength())
        throw OutOfIndexException("out of range");
    else{
        return arr[index];
    }
}
/*
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
}*/

template<typename T>
Vector<T>& Vector<T> :: operator += (const Vector<T>& vect)
{
    int maxSize = this->size;
    int minSize = vect.size;
    Vector<T> minVector = vect;
    Vector<T> maxVector = *this;
    if(maxSize!=minSize){
        int maxSize = std::max(vect.size, this->size);
        int minSize = std::min(vect.size, this->size);
        minVector = (this->size <= vect.size) ? *this : vect;
        maxVector = (this->size < vect.size) ? vect : *this;
    }
    T* tempArr = new T[maxSize];
    for (int i = 0; i < minSize; i++) {
        tempArr[i] = minVector.arr[i] + maxVector.arr[i];
    }

    // Копируем оставшиеся элементы из большего вектора
    for (int i = minSize; i < maxSize; i++) {
        tempArr[i] = maxVector.arr[i];
    }

    // Освобождаем память старого массива
    delete[] this->arr;

    // Обновляем указатель на новый массив и размер
    this->arr = tempArr;
    this->size = maxSize;

    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& vect)
{   //Хитро сделал второй операнд отрицательным и потом вызвал обычное сложение
    Vector<T> tempVec = vect;
    tempVec *= -1;
    return *this+=tempVec;
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
Vector<T>& Vector<T>::operator/=(const T& val) {
    if(val == 0)
        throw DevideByZeroException("dividing by 0");
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
    int maxSize = v1.size;
    int minSize = v2.size;
    Vector<T> minVector = v2;
    Vector<T> maxVector = v1;
    if(maxSize!=minSize){
        int maxSize = std::max(v2.size, v1.size);
        int minSize = std::min(v2.size, v1->size);
        minVector = (v1.size <= v2.size) ? v1 : v2;
        maxVector = (v1.size < v2.size) ? v2 : v1;
    }
    T* tempArr = new T[maxSize];
    for (int i = 0; i < minSize; i++) {
        tempArr[i] = minVector.arr[i] + maxVector.arr[i];
    }


    for (int i = minSize; i < maxSize; i++) {
        tempArr[i] = maxVector.arr[i];
    }


    Vector<T> tempVec (maxSize);
    tempVec->arr = tempArr;
    tempVec->size = maxSize;
    return tempVec;
}
template<typename T>
Vector<T> operator -(const Vector<T>& v1, const Vector<T>& v2){
    Vector<T> tempVec = v2;
    tempVec *= -1;
    return v1+=tempVec;
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
    if(val == 0)
        throw DevideByZeroException("dividing by 0");
    Vector<T> tempVec(v1.size);
    for (int i = 0; i < v1.size; i++) {
        tempVec.set_elem(i, v1.arr[i] / val);
    }
    return tempVec;
}
#endif // VECTOR_HPP
