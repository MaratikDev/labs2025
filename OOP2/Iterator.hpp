#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "Iterator.h"

template <typename T>
Iterator<T>::Iterator(Vector<T>& containerObj): containerObj(containerObj) {
    this->index = 0;
}

template <typename T>
Iterator<T> Iterator<T>::next() {
    if (index < containerObj.getLength()) {
        index++;
    }
    return *this;
}

template <typename T>
T& Iterator<T>::value() {
    return this->containerObj.getElem(index);
}

template <typename T>
bool Iterator<T>::isEnd() {
    return index >= containerObj.getLength();
}


template <typename T>
T& Iterator<T>::operator*() {
    return containerObj.getElem(index);
}
template <typename T>
bool Iterator<T>::operator ==(Iterator<T>& b) {
    return &containerObj == &b.containerObj && index == b.index;
}

template <typename T>
bool Iterator<T>::operator !=(Iterator<T>& b) {
    return !(&containerObj == &b.containerObj && index == b.index);
}
template <typename T>
Iterator<T>& Iterator<T>::operator++(){
    if (index < containerObj.getLength()) {
        index++;
    }
    return *this;
}
#endif // ITERATOR_HPP
