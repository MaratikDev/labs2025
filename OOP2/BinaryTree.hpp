#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP
#include "BinaryTree.h"


template<typename T>
void BinaryTree<T>::insert(T value, TreeNode<T>*& node){
    if(node == nullptr){
        node = new TreeNode<T>(value);
    }
    else{
        if(value <= node->data){
            insert(value, node->left);
        }
        else{
            insert(value, node->right);
        }
    }
}

template<typename T>
bool BinaryTree<T>::contains(T value, TreeNode<T>* node){
    bool result;
    if(node == nullptr){
        result = false;
    }
    else if(value == node->data){
        result = true;
    }
    else{
        if(value <= node->data){
            result = contains(value, node->left);
        }
        else{
            result = contains(value, node->right);
        }
    }
    return result;
}
template<typename T>
bool BinaryTree<T>::remove(T value, TreeNode<T>*& node){
    bool result;
    if(node == nullptr){
        result = false;
    }
    else if(value == node->data){
        if(node->left == nullptr && node->right == nullptr){
            delete node;
            node = nullptr;
        }
        else if(node->left != nullptr && node->right == nullptr){
            TreeNode<T>* temp = node;
            node = node->left;
            delete temp;
        }
        else if(node->left == nullptr && node->right != nullptr){
            TreeNode<T>* temp = node;
            node = node->right;
            delete temp;
        }
        else{
            TreeNode<T>* minNode = findMin(node->right); //что это
            node->data = minNode->data;
            remove(minNode->data, node->right);
        }
        result = true;
    }
    return result;
}
template<typename T>
TreeNode<T>& BinaryTree<T>::findMin(TreeNode<T>* node){
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
template<typename T>
std::string BinaryTree<T>::treeAsString(const TreeNode<T>* node) const  {
    if (node == nullptr) {
        return "{}";
    }

    std::string leftStr = treeAsString(node->left);
    std::string rightStr = treeAsString(node->right);

    // Преобразуем данные узла в строку
    std::string nodeDataStr;
    if (typeid(T) == typeid(std::string)) {
        nodeDataStr = node->data;
    } else if (typeid(T) == typeid(char)) {
        nodeDataStr = std::string(1, node->data);
    } else {
        nodeDataStr = std::to_string(node->data);
    }

    return "{" + nodeDataStr + ", " + leftStr + ", " + rightStr + "}";
}
template<typename T>
void BinaryTree<T>::clear(TreeNode<T>* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}



#endif // BINARYTREE_HPP
