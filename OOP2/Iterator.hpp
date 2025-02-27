#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "Iterator.h"

template <typename T>
Iterator<T>::Iterator(Vector<T>& container_obj): container_obj(container_obj) {
    this->index = 0;
}

template <typename T>
Iterator<T> Iterator<T>::next() {
    if (index < container_obj.get_length()) {
        index++;
    }
    return *this;
}

template <typename T>
T& Iterator<T>::value() {
    return this->container_obj.get_elem(index);
}

template <typename T>
bool Iterator<T>::is_end() {
    return index >= container_obj.get_length();
}


template <typename T>
T& Iterator<T>::operator*() {
    return container_obj.get_elem(index);
}
template <typename T>
bool Iterator<T>::operator ==(Iterator<T>& b) {
    return &container_obj == &b.container_obj && index == b.index;
}

template <typename T>
bool Iterator<T>::operator !=(Iterator<T>& b) {
    return !(&container_obj == &b.container_obj && index == b.index);
}
#endif // ITERATOR_HPP
