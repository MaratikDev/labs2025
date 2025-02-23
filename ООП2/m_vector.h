#ifndef M_VECTOR_H
#define M_VECTOR_H

#include <iostream>
#include <initializer_list>
#include "Iterator.h"

template <typename T>
class m_vector {
private:
    T *arr;
    int size;

public:

    m_vector(int length);
    explicit m_vector(std::initializer_list<T>& lst);
    m_vector(const m_vector<T>& vect);
    ~m_vector();

    int get_length();
    void set_elem(int index, const T& elem);

    T& get_elem(int index);
    T* to_array();
    T& operator[](int index);

    m_vector<T>& operator = (const m_vector<T>& lst);
    m_vector<T>& operator += (const m_vector<T>& vect);
    m_vector<T>& operator -= (const m_vector<T>& vect);
    m_vector<T>& operator *= (const T& val);
    m_vector<T>& operator /= (const T& val);

    friend std::ostream& operator << (std::ostream& os, const m_vector<T>& lst){
        os << "mat vect: ";
        for (int i = 0; i < lst.size; i++) {
            os << lst.arr[i] << " ";
        }
        return os;
    }
    friend m_vector<T> operator +(const m_vector<T>& v1, const m_vector<T>& v2){
        int tempSize = std::max(v1.size, v2.size);
        m_vector<T> tempVec (tempSize);
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
    friend m_vector<T> operator -(const m_vector<T>& v1, const m_vector<T>& v2){
        int tempSize = std::max(v1.size, v2.size);
        m_vector<T> tempVec(tempSize);
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
    friend m_vector<T> operator *(const m_vector<T>& v1, const T& val){
        m_vector<T> tempVec(v1.size);
        for (int i = 0; i < v1.size; i++) {
            tempVec.set_elem(i, v1.arr[i] * val);
        }
        return tempVec;
    }
    friend m_vector<T> operator /(const m_vector<T>& v1, const T& val){
        m_vector<T> tempVec(v1.size);
        for (int i = 0; i < v1.size; i++) {
            tempVec.set_elem(i, v1.arr[i] / val);
        }
        return tempVec;
    }
    Iterator<T> iterator_begin();
    Iterator<T> iterator_end();
};
template<typename T>
Iterator<T> m_vector<T>::iterator_begin(){
    return Iterator<T>(*this);
}
template<typename T>
Iterator<T> m_vector<T>::iterator_end(){
    Iterator<T> iter(*this);
    while(!iter.is_end()){
        iter.next();
    }
    return iter;
}

template<typename T>
m_vector<T>::m_vector(int length) {
    this->size = length;
    this->arr = new T[size];
}

template<typename T>
m_vector<T>::m_vector(std::initializer_list<T>& lst) {
    this->arr = new T[lst.size()];
    this->size = lst.size();
    int i = 0;
    for (T elem : lst) {
        arr[i++] = elem;
    }
}

template<typename T>
m_vector<T>::m_vector(const m_vector<T>& vect) {
    this->size = vect.size;
    this->arr = new T[size];
    for (int i = 0; i < size; i++) {
        this->arr[i] = vect.arr[i];
    }
}

template<typename T>
m_vector<T>::~m_vector() {
    delete[] arr;
}

template<typename T>
m_vector<T>& m_vector<T> :: operator = (const m_vector<T>& lst) {
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
int m_vector<T>::get_length() {
    return this->size;
}

template<typename T>
void m_vector<T>::set_elem(int index, const T& elem) {
    arr[index] = elem;
}

template<typename T>
T& m_vector<T>::get_elem(int index) {
    return arr[index];
}

template<typename T>
T* m_vector<T>::to_array() {
    T* array = new T[this->size];
    for (int i = 0; i < this->size; i++) {
        array[i] = this->arr[i];
    }
    return array;
}

template<typename T>
T& m_vector<T>::operator[](int index) {
    return arr[index];
}

template<typename T>
m_vector<T>& m_vector<T> :: operator += (const m_vector<T>& vect)
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
m_vector<T>& m_vector<T>::operator-=(const m_vector<T>& vect)
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
m_vector<T>& m_vector<T>::operator*=(const T& val)
{
    int i = 0;
    for (i; i < this->size; i++) {
        this->arr[i] = this->arr[i] * val;
    }

    return *this;
}

template<typename T>
m_vector<T>& m_vector<T>::operator/=(const T& val)
{
    int i = 0;
    for (i; i < this->size; i++) {
        this->arr[i] = this->arr[i] / val;
    }

    return *this;
}


#endif // M_VECTOR_H
