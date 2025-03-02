#ifndef ITERATORBINTREE_HPP
#define ITERATORBINTREE_HPP
#include "IteratorBinTree.h"
/*
template <typename T>
IteratorBinTree<T>::IteratorBinTree(BinaryTree<T>& container_obj): container_obj(container_obj) {
    if (container_obj.root != nullptr) {
        queue.push(container_obj.root);
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
    throw ("Iterator is at the end");
}
template <typename T>
bool IteratorBinTree<T>::is_end() {
    return queue.empty();
}

template <typename T>
T& IteratorBinTree<T>::operator*()  {
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
*/

#endif // ITERATORBINTREE_H
