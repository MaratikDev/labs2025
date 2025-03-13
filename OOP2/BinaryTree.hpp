#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP
#include "BinaryTree.h"
#include <iostream>
#include <fstream>
#include <filesystem>

template<typename T>
void BinaryTree<T>::generateGraphVizHelper(TreeNode<T>* node, std::ofstream& dotFile) {
    if (node == nullptr) {
        return;
    }

    if (node->left != nullptr) {
        dotFile << node->data << "->" << node->left->data << ";\n";
        generateGraphVizHelper(node->left, dotFile); // Рекурсивный обход левого поддерева
    }
    if (node->right != nullptr) {
        dotFile << node->data << "->" << node->right->data << ";\n";
        generateGraphVizHelper(node->right, dotFile); // Рекурсивный обход правого поддерева
    }
}
template<typename T>
int BinaryTree<T>::showGraph(const std::string& filename){
    const std::string cmdRequest = "dot -Tpng " +filename+".dot -o"+filename+".png";
    system(cmdRequest.c_str());
    const std::string cmdRequest1 = "start "+filename+".png";
    return system(cmdRequest1.c_str());
}

template<typename T>
void BinaryTree<T>::generateGraphViz(const std::string& filename){
    std::ofstream dotFile(filename+".dot");
    if (!dotFile.is_open()) {
        throw FileException ("Failed to open file: ");
        return;
    }

    TreeNode<T>* current = getRoot();
    if (current == nullptr) {
        throw EmptyException ("Tree is empty!");
        dotFile.close();
        return;
    }

    dotFile << "digraph MyGraph {\n";
    generateGraphVizHelper(current, dotFile);
    dotFile << "}\n";
    dotFile.close();
}
template<typename T>
BinaryTree<T>::BinaryTree() : root(nullptr){}

template<typename T>
BinaryTree<T>::~BinaryTree(){
    clear(root);
}
template<typename T>
BinaryTree<T>::BinaryTree(BinaryTree<T>&& otherTree) {
    root = otherTree.root;
    otherTree.root = nullptr;
}
template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& otherTree) {
    if (this != &otherTree) {
        clear(root);
        root = copyTree(otherTree.root);
    }
}
template<typename T>
TreeNode<T>* BinaryTree<T>::getRoot() const {
    return root;
}
template<typename T>
std::ostream& operator << (std::ostream& os, const BinaryTree<T>& tree){
    os << tree.treeAsString(tree.root);
    return os;
}
template<typename T>
void BinaryTree<T>::insert(T value){
    insert(value, root);
}
template<typename T>
bool BinaryTree<T>::contains(T value){
    return contains(value, root);
}
template<typename T>
bool BinaryTree<T>::remove(T value){
    return this->remove(value, root);
}

template<typename T>
BinaryTree<T>::BinaryTree(std::initializer_list<T>& lst): root(nullptr){
    for (const auto& item : lst) {
        this->insert(item);
    }
}
template<typename T>
T* BinaryTree<T>::toArray(){
    IteratorBinTree<T> iter = this->begin();
    std::vector<T> elements;
    while(!iter.is_end()){
        elements.push_back(iter.value());
        iter.next();
    }
    T* result = new T[elements.size()];
    std::copy(elements.begin(), elements.end(), result);
    return result;
}
template<typename T>
BinaryTree<T>& BinaryTree<T>::operator = (const BinaryTree<T>& lst){
    if (this != &lst) {
        clear(root);
        root = copyTree(lst.root);
    }
    return *this;
}
template<typename T>
BinaryTree<T>& BinaryTree<T>::operator *= (const T& val){
    multiply(root, val);
    return *this;
}
template<typename T>
BinaryTree<T>& BinaryTree<T>::operator /= (const T& val){
    if(val == 0)
        throw DevideByZeroException("dividing by 0");
    divide(root, val);
    return *this;
}
template<typename T>
BinaryTree<T> operator *(const BinaryTree<T>& v1, const T& val){
    BinaryTree<T> result(v1);
    result *= val;
    return result;
}
template<typename T>
BinaryTree<T> operator /(const BinaryTree<T>& v1, const T& val){
    if(val == 0)
        throw DevideByZeroException("dividing by 0");
    BinaryTree<T> result(v1);
    result /= val;
    return result;
}
template<typename T>
IteratorBinTree<T> BinaryTree<T>::begin(){
    return IteratorBinTree<T>(*this);
}
template<typename T>
StaticIteratorBinTree<T> BinaryTree<T>::beginStatic(){
    return StaticIteratorBinTree<T>(*this);
}
template<typename T>
TreeNode<T>* BinaryTree<T>::copyTree(const TreeNode<T>* node) const {
    if (node == nullptr) {
        return nullptr;
    }
    TreeNode<T>* newNode = new TreeNode<T>(node->data);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}
template<typename T>
void BinaryTree<T>::multiply(TreeNode<T>* node, const T& val) {
    if (node != nullptr) {
        node->data *= val;
        multiply(node->left, val);
        multiply(node->right, val);
    }
}
template<typename T>
void BinaryTree<T>::divide(TreeNode<T>* node, const T& val) {
    if(val == 0)
        throw DevideByZeroException("dividing by 0");
    if (node != nullptr) {
        node->data /= val;
        divide(node->left, val);
        divide(node->right, val);
    }
}

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
    if (node == nullptr) {
        result = false;
    }

    else if (value < node->data) {
        result = remove(value, node->left);
    }
    else if (value > node->data) {
        result = remove(value, node->right);
    }
    else {

        if (node->left == nullptr && node->right == nullptr) {

            delete node;
            node = nullptr;
        } else if (node->left == nullptr) {

            TreeNode<T>* temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            TreeNode<T>* temp = node;
            node = node->left;
            delete temp;
        } else {

            TreeNode<T>* minNode = findMin(node->right);
            node->data = minNode->data;
            remove(minNode->data, node->right);
        }
        result = true;
    }
    return result;
}
template<typename T>
TreeNode<T>* BinaryTree<T>::findMin(TreeNode<T>* node){
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
    std::string nodeDataStr = treeAsStringHelper(node->data);


    return "{" + nodeDataStr + ", " + leftStr + ", " + rightStr + "}";
}
template <typename T>
std::string BinaryTree<T>::treeAsStringHelper(const T& data) {
    return std::to_string(data);
}

template <typename T>
std::string BinaryTree<T>::treeAsStringHelper(const std::string& data) {
    return data;
}

template <typename T>
std::string BinaryTree<T>::treeAsStringHelper(const char& data) {
    return std::string(1, data);
}
template<typename T>
TreeNode<T>* BinaryTree<T>::getRoot(){
    return root;
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
