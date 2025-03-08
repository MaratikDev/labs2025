#ifndef STATICTREEITERATOR_HPP
#define STATICTREEITERATOR_HPP
#include "StaticTreeIterator.h"

template <typename T>
StaticIteratorBinTree<T>::StaticIteratorBinTree(const BinaryTree<T>& container_obj) : container_obj(container_obj) {
    if (container_obj.getRoot() != nullptr) {
        queue.push(container_obj.getRoot());
    }
}

template <typename T>
StaticIteratorBinTree<T> StaticIteratorBinTree<T>::next() {
    if (!queue.empty()) {
        const TreeNode<T>* current = queue.front();
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
const T& StaticIteratorBinTree<T>::value() const {
    if (!queue.empty()) {
        return queue.front()->data;
    }
    throw EmptyException("Iterator is at the end");
}
template <typename T>
bool StaticIteratorBinTree<T>::is_end() const {
    return queue.empty();
}
template <typename T>
StaticIteratorBinTree<T>& StaticIteratorBinTree<T>::operator++() {
    next();
    return *this;
}
template <typename T>
const T& StaticIteratorBinTree<T>::operator*() const {
    return value();
}
template <typename T>
bool StaticIteratorBinTree<T>::operator==(const StaticIteratorBinTree<T>& b) const {
    return &container_obj == &b.container_obj && queue == b.queue;
}
template <typename T>
bool StaticIteratorBinTree<T>::operator!=(const StaticIteratorBinTree<T>& b) const {
    return !(*this == b);
}

#endif // STATICTREEITERATOR_HPP
