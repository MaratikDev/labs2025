#ifndef ITERATORBINTREE_HPP
#define ITERATORBINTREE_HPP
#include "IteratorBinTree.h"
template <typename T>
IteratorBinTree<T>::IteratorBinTree(BinaryTree<T>& container_obj): container_obj(container_obj) {
}

template <typename T>
IteratorBinTree<T> IteratorBinTree<T>::next() {
    container_obj.
    return *this;
}

template <typename T>
T& IteratorBinTree<T>::value() {
    return this->container_obj.get_elem(index);
}

template <typename T>
bool IteratorBinTree<T>::is_end() {
    return index >= container_obj.get_length();
}


template <typename T>
T& IteratorBinTree<T>::operator*() {
    return container_obj.get_elem(index);
}
template <typename T>
bool IteratorBinTree<T>::operator ==(IteratorBinTree<T>& b) {
    return &container_obj == &b.container_obj && index == b.index;
}

template <typename T>
bool IteratorBinTree<T>::operator !=(IteratorBinTree<T>& b) {
    return !(&container_obj == &b.container_obj && index == b.index);
}
#endif // ITERATORBINTREE_H
