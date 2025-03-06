#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP
#include "BinaryTree.h"



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
