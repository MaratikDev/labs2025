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
    std::queue<TreeNode<T>*> queue;
public:

    IteratorBinTree<T>(BinaryTree<T>& container_obj): container_obj(container_obj) {
        if (container_obj.root != nullptr) {
            queue.push(container_obj.root);
        }
    }
    IteratorBinTree<T> next() {
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

    T& value() {
        if (!queue.empty()) {
            return queue.front()->data;
        }
        throw ("Iterator is at the end");
    }

    bool is_end() {
        return queue.empty();
    }

    IteratorBinTree<T> &operator++() {
        next();
        return *this;
    }

    T& operator*()  {
        return value();
    }

    bool operator ==(IteratorBinTree<T>& b) {
        return &container_obj == &b.container_obj && queue == b.queue;
    }

    bool operator !=(IteratorBinTree<T>& b) {
        return !(*this == b);
    }
};
#endif // ITERATORBINTREE_H
