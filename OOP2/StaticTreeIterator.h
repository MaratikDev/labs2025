#ifndef STATICTREEITERATOR_H
#define STATICTREEITERATOR_H
#include <queue>
#include "TreeNode.h"
#include "exceptions.h"

template <typename T>
class BinaryTree;

template <typename T>
class StaticIteratorBinTree {
private:
    const BinaryTree<T>& container_obj;
    std::queue<const TreeNode<T>*> queue;

public:
    StaticIteratorBinTree(const BinaryTree<T>& container_obj);
    StaticIteratorBinTree<T> next();
    const T& value() const ;
    bool is_end() const;
    StaticIteratorBinTree<T>& operator++();
    const T& operator*() const;
    bool operator==(const StaticIteratorBinTree<T>& b) const;
    bool operator!=(const StaticIteratorBinTree<T>& b) const;
};
#endif // STATICTREEITERATOR_H
