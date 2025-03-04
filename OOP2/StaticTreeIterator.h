#ifndef STATICTREEITERATOR_H
#define STATICTREEITERATOR_H
#include <queue>
#include "TreeNode.h"


template <typename T>
class BinaryTree;

template <typename T>
class StaticIteratorBinTree {
private:
    const BinaryTree<T>& container_obj;
    std::queue<const TreeNode<T>*> queue;

public:
    StaticIteratorBinTree(const BinaryTree<T>& container_obj) : container_obj(container_obj) {
        if (container_obj.getRoot() != nullptr) {
            queue.push(container_obj.getRoot());
        }
    }


    StaticIteratorBinTree<T> next() {
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
    const T& value() const {
        if (!queue.empty()) {
            return queue.front()->data;
        }
        throw ("Iterator is at the end");
    }
    bool is_end() const {
        return queue.empty();
    }
    StaticIteratorBinTree<T>& operator++() {
        next();
        return *this;
    }
    const T& operator*() const {
        return value();
    }
    bool operator==(const StaticIteratorBinTree<T>& b) const {
        return &container_obj == &b.container_obj && queue == b.queue;
    }
    bool operator!=(const StaticIteratorBinTree<T>& b) const {
        return !(*this == b);
    }
};
#endif // STATICTREEITERATOR_H
