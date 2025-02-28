#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "IteratorBinTree.h"
#include "TreeNode.h"
#include <iostream>
#include <iostream>
#include <string>
#include <queue>

template <typename T>
class BinaryTree
{
public:
    BinaryTree() : root(nullptr){}
    ~BinaryTree(){
        clear(root);
    }
    friend std::ostream& operator << (std::ostream& os, const BinaryTree<T>& tree){
        os << tree.treeAsString(tree.root);
        return os;
    }

    void insert(T value){
        insert(value, root);
    }
    bool contains(T value){
        return contains(value, root);
    }
    bool remove(T value){
        this->remove(value, root);
    }


    explicit BinaryTree(std::initializer_list<T>& lst): root(nullptr){
        for (const auto& item : lst) {
            this->insert(item);
        }
    }

    T* toArray(){
        std::vector<T> elements;
        std::queue<TreeNode<T>*> queue;
        if (root) queue.push(root);

        while (!queue.empty()) {
            TreeNode<T>* node = queue.front();
            queue.pop();
            elements.push_back(node->data);

            if (node->left) queue.push(node->left);
            if (node->right) queue.push(node->right);
        }

        T* result = new T[elements.size()];
        std::copy(elements.begin(), elements.end(), result);
        return result;
    }

    BinaryTree<T>& operator = (const BinaryTree<T>& lst){
        if (this != &lst) {
            clear(root);
            root = copyTree(lst.root);
        }
        return *this;
    }
    BinaryTree<T>& operator *= (const T& val){
        multiply(root, val);
        return *this;
    }
    BinaryTree<T>& operator /= (const T& val){
        devide(root, val);
        return *this;
    }
    friend BinaryTree<T> operator *(const BinaryTree<T>& v1, const T& val){
        BinaryTree<T> result(v1);
        result *= val;
        return result;
    }
    friend BinaryTree<T> operator /(const BinaryTree<T>& v1, const T& val){
        BinaryTree<T> result(v1);
        result /= val;
        return result;
    }

    IteratorBinTree<T> begin(){
        return IteratorBinTree<T>(nullptr);
    }
    TreeNode<T>* copyTree(const TreeNode<T>* node) const {
        if (node == nullptr) {
            return nullptr;
        }
        TreeNode<T>* newNode = new TreeNode<T>(node->data);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

    template<typename T>
    void multiply(TreeNode<T>* node, const T& val) {
        if (node != nullptr) {
            node->data *= val;
            multiply(node->left, val);
            multiply(node->right, val);
        }
    }
    void divide(TreeNode<T>* node, const T& val) {
        if (node != nullptr) {
            node->data /= val;
            divide(node->left, val);
            divide(node->right, val);
        }
    }

private:


    TreeNode<T>* root;
    void insert(T value, TreeNode<T>*& node);
    bool contains(T value, TreeNode<T>* node);
    bool remove(T value, TreeNode<T>*& node);
    TreeNode<T>& findMin(TreeNode<T>* node);
    std::string treeAsString(const TreeNode<T>* node) const;
    void clear(TreeNode<T>* node);


};

#endif // BINARYTREE_H
