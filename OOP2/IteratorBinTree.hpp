#ifndef ITERATORBINTREE_HPP
#define ITERATORBINTREE_HPP
#include "IteratorBinTree.h"

template <typename T>
IteratorBinTree<T>::IteratorBinTree(BinaryTree<T>& container_obj): container_obj(container_obj) {
    if (container_obj.getRoot() != nullptr) {
        queue.push(container_obj.getRoot());
    }
}
template <typename T>
IteratorBinTree<T> IteratorBinTree<T>::next() {
    if (!queue.empty()) {
        TreeNode<T>* current = queue.front();
        queue.pop();

        if (current->left != nullptr) {
            queue.push(current->left);
        }
        if (current->right != nullptr) {
            queue.push(current->right);
        }
    }
    return *this;
}
template <typename T>
T& IteratorBinTree<T>::value() {
    if (!queue.empty()) {
        return queue.front()->data;
    }
    throw EmptyException("Iterator is at the end");
}
template <typename T>
bool IteratorBinTree<T>::is_end() {
    return queue.empty();
}

template <typename T>
T& IteratorBinTree<T>::operator*() {
    return value();
}
template <typename T>
bool IteratorBinTree<T>::operator ==(IteratorBinTree<T>& b) {
    return &container_obj == &b.container_obj && queue == b.queue;
}
template <typename T>
bool IteratorBinTree<T>::operator !=(IteratorBinTree<T>& b) {
    return !(*this == b);
}
template <typename T>
IteratorBinTree<T>& IteratorBinTree<T>::operator++() {
    next();
    return *this;
}


#endif // ITERATORBINTREE_HPP
