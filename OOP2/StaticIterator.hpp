#ifndef STATICITERATOR_HPP
#define STATICITERATOR_HPP
#include "StaticIterator.h"

template <typename T>
StaticIterator<T>::StaticIterator(const  Vector<T>& containerObj): containerObj(containerObj) {
    this->index = 0;
}

template <typename T>
StaticIterator<T> StaticIterator<T>::next() {
    if (index < containerObj.getLength()) {
        index++;
    }
    return *this;
}

template <typename T>
const T& StaticIterator<T>::value() const{
    return this->containerObj.getElem(index);
}

template <typename T>
bool StaticIterator<T>::isEnd() const{
    return index >= containerObj.getLength();
}


template <typename T>
const T& StaticIterator<T>::operator*() const{
    return containerObj.getElem(index);
}
template <typename T>
bool StaticIterator<T>::operator ==(StaticIterator<T>& b) const{
    return &containerObj == &b.containerObj && index == b.index;
}

template <typename T>
bool StaticIterator<T>::operator !=(StaticIterator<T>& b) const{
    return !(&containerObj == &b.containerObj && index == b.index);
}
template <typename T>
StaticIterator<T>& StaticIterator<T>::operator++() {
    if (index < containerObj.getLength()) {
        index++;
    }
    return *this;
}
#endif // STATICITERATOR_HPP
