#ifndef ITERATORBINTREE_H
#define ITERATORBINTREE_H
#include <queue>
#include "TreeNode.h"
template <typename T>
class BinaryTree;

template <typename T>
class IteratorBinTree {
private:
    BinaryTree<T>& container_obj;
    std::queue<TreeNode<T>> queue;
public:

    IteratorBinTree<T>(BinaryTree<T>& container_obj);
    IteratorBinTree<T> next();
    T& value();
    bool is_end();
    IteratorBinTree<T> &operator++();
    T& operator*();
    bool operator ==(IteratorBinTree<T>& b);
    bool operator !=(IteratorBinTree<T>& b);
};
#endif // ITERATORBINTREE_H
