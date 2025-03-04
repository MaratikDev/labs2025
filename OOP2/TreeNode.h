#ifndef TREENODE_H
#define TREENODE_H
template <typename T>
struct TreeNode //тк это структура то тут по дефолту паблик все
{
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;

    TreeNode(T data): data(data), left(nullptr), right(nullptr) {}
};
#endif // TREENODE_H
