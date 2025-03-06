#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "IteratorBinTree.h"
#include "StaticTreeIterator.h"
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <queue>
#include "exceptions.h"
template <typename T>
class BinaryTree
{
public:
    BinaryTree();
    BinaryTree<T>(BinaryTree<T>&& otherTree);
    BinaryTree<T>(const BinaryTree<T>& otherTree);
    ~BinaryTree();
    friend std::ostream& operator << (std::ostream& os, const BinaryTree<T>& tree);

    void insert(T value);
    bool contains(T value);
    bool remove(T value);


    explicit BinaryTree(std::initializer_list<T>& lst);

    T* toArray();

    BinaryTree<T>& operator = (const BinaryTree<T>& lst);
    BinaryTree<T>& operator *= (const T& val);
    BinaryTree<T>& operator /= (const T& val);
    friend BinaryTree<T> operator *(const BinaryTree<T>& v1, const T& val);
    friend BinaryTree<T> operator /(const BinaryTree<T>& v1, const T& val);
    IteratorBinTree<T> begin();
    StaticIteratorBinTree<T> beginStatic();
    TreeNode<T>* copyTree(const TreeNode<T>* node) const;
    void multiply(TreeNode<T>* node, const T& val);
    void divide(TreeNode<T>* node, const T& val);
    TreeNode<T>* getRoot() const ;

private:
    TreeNode<T>* root;
    //вспомогательные функции что б не приходилось как доп параметр this->root писать (умно)
    void insert(T value, TreeNode<T>*& node);
    bool contains(T value, TreeNode<T>* node);
    bool remove(T value, TreeNode<T>*& node);
    TreeNode<T>* findMin(TreeNode<T>* node);
    std::string treeAsString(const TreeNode<T>* node) const;
    void clear(TreeNode<T>* node);


};

#endif // BINARYTREE_H
