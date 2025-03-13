#include <iostream>
#include <cassert>
#include "BinaryTree.hpp"
#include "Iterator.hpp"
#include "Vector.hpp"
#include "exceptions.h"
#include "IteratorBinTree.hpp"
#include "StaticTreeIterator.hpp"
#include "StaticIterator.hpp"
void test_vector() {
    // initializer list
    std::initializer_list<int> lst = {1, 2, 3, 4};
    Vector<int> v1(lst);
    assert(v1.getLength() == 4);
    assert(v1[0] == 1);
    assert(v1[1] == 2);
    assert(v1[2] == 3);
    assert(v1[3] == 4);
    try {
        v1[4];
        assert(false);
    } catch (const OutOfIndexException& e) {
        assert(std::string(e.what()) == "out of range");
    }

    // copy
    Vector<int> v2(v1);
    assert(v2.getLength() == 4);
    assert(v2[0] == 1);
    assert(v2[1] == 2);
    assert(v2[2] == 3);
    assert(v2[3] == 4);

    // =
    Vector<int> v3 = v1;
    assert(v3.getLength() == 4);
    assert(v3[0] == 1);
    assert(v3[1] == 2);
    assert(v3[2] == 3);
    assert(v3[3] == 4);

    // +=
    Vector<int> v4(lst);
    v4 += v1;
    assert(v4[0] == 2);
    assert(v4[1] == 4);
    assert(v4[2] == 6);
    assert(v4[3] == 8);

    // -=
    v4 -= v1;
    assert(v4[0] == 1);
    assert(v4[1] == 2);
    assert(v4[2] == 3);
    assert(v4[3] == 4);

    // *=
    v4 *= 2;
    assert(v4[0] == 2);
    assert(v4[1] == 4);
    assert(v4[2] == 6);
    assert(v4[3] == 8);

    // /=
    v4 /= 2;
    assert(v4[0] == 1);
    assert(v4[1] == 2);
    assert(v4[2] == 3);
    assert(v4[3] == 4);

    try {
        v4 /= 0;
        assert(false);
    } catch (const DevideByZeroException& e) {
        assert(std::string(e.what()) == "dividing by 0");
    }

    //to_array
    int* arr = v4.toArray();
    assert(arr[0] == 1);
    assert(arr[1] == 2);
    assert(arr[2] == 3);
    assert(arr[3] == 4);
    delete[] arr;

    std::cout << "All Vector tests passed!" << std::endl;

    {
        std::initializer_list<int> lst = {1, 2, 3, 4};
        Vector<int> v1(lst);
        Vector<int> v2 = std::move(v1);

        assert(v1.getLength() == 0);
        assert(v2.getElem(0) == 1);
        assert(v2.getElem(1) == 2);
        assert(v2.getElem(2) == 3);
    }
}

void test_iterator() {
    std::initializer_list<int> lst = {1, 2, 3, 4};
    Vector<int> v1(lst);

    // begin and end
    Iterator<int> it = v1.begin();
    StaticIterator<int> itStatic = v1.beginStatic();
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 3);
    ++it;
    assert(*it == 4);
    ++it;
    assert(it.isEnd());

    assert(*itStatic == 1);
    ++itStatic;
    assert(*itStatic == 2);
    ++itStatic;
    assert(*itStatic == 3);
    ++itStatic;
    assert(*itStatic == 4);
    ++itStatic;
    assert(itStatic.isEnd());

    // ==
    Iterator<int> it2 = v1.begin();
    Iterator<int> it3 = v1.begin();
    assert(it3 == it2);

    // !=
    ++it3;
    assert(it3 != it2);

    std::cout << "All Iterator tests passed!" << std::endl;
}

void testBinaryTree() {
    // insert
    {
        BinaryTree<int> tree;
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(4);
        tree.insert(6);
        tree.insert(8);

        assert(tree.contains(5) == true);
        assert(tree.contains(3) == true);
        assert(tree.contains(7) == true);
        assert(tree.contains(2) == true);
        assert(tree.contains(4) == true);
        assert(tree.contains(6) == true);
        assert(tree.contains(8) == true);
        assert(tree.contains(10) == false);


        //std::initializer
        std::initializer_list<int>lst1 = {1};
        BinaryTree<int> tree1(lst1);
        assert(tree1.contains(1) == true);

        std::initializer_list<int>lst2 = {1, 2, 3};
        BinaryTree<int> tree2(lst2);
        assert(tree2.contains(1) == true);
        assert(tree2.contains(2) == true);
        assert(tree2.contains(3) == true);
    }

    // remove
    {
        BinaryTree<int> tree;
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(4);
        tree.insert(6);
        tree.insert(8);

        assert(tree.remove(5) == true);
        assert(tree.contains(5) == false);
        assert(tree.remove(3) == true);
        assert(tree.contains(3) == false);
        assert(tree.remove(10) == false);
    }

    //  toArray
    {
        BinaryTree<int> tree;
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);

        int* arr = tree.toArray();
        assert(arr[0] == 5);
        assert(arr[1] == 3);
        assert(arr[2] == 7);
        delete[] arr;
    }

    //  div 0
    {
        BinaryTree<int> tree;
        tree.insert(10);
        tree.insert(20);

        try {
            tree /= 0;
            assert(false);
        } catch (const DevideByZeroException& e) {
            assert(std::string(e.what()) == "dividing by 0");
        }
    }
    {
        BinaryTree<int> tree;
        tree.insert(10);
        tree.insert(20);
        BinaryTree<int> tree1 = std::move(tree);
        assert(tree.getRoot() == nullptr);
        int* arr = tree1.toArray();
        assert(arr[0] == 10);
        assert(arr[1] == 20);

    }

    std::cout << "All BinaryTree tests passed!" << std::endl;
}

void testBinaryTreeIterator() {
    // iter
    {
        BinaryTree<int> tree;
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(4);
        tree.insert(6);
        tree.insert(8);


        IteratorBinTree<int> it = tree.begin();
        assert(*it == 5);
        ++it;
        assert(*it == 3);
        ++it;
        assert(*it == 7);
        ++it;
        assert(*it == 2);
        ++it;
        assert(*it == 4);
        ++it;
        assert(*it == 6);
        ++it;
        assert(*it == 8);
        ++it;
        assert(it.is_end() == true);

        StaticIteratorBinTree<int> itStaticTree = tree.beginStatic();
        assert(*itStaticTree == 5);
        ++itStaticTree;
        assert(*itStaticTree == 3);
        ++itStaticTree;
        assert(*itStaticTree == 7);
        ++itStaticTree;
        assert(*itStaticTree == 2);
        ++itStaticTree;
        assert(*itStaticTree == 4);
        ++itStaticTree;
        assert(*itStaticTree == 6);
        ++itStaticTree;
        assert(*itStaticTree == 8);
        ++itStaticTree;
        assert(itStaticTree.is_end() == true);


    }
    // == !=
    {
        BinaryTree<int> tree;
        tree.insert(5);
        tree.insert(3);

        IteratorBinTree<int> it1 = tree.begin();
        IteratorBinTree<int> it2 = tree.begin();

        assert(it1 == it2);
        ++it1;
        assert(it1 != it2);
    }

    std::cout << "All BinaryTreeIterator tests passed!" << std::endl;
}

int main() {
    test_vector();
    test_iterator();
    testBinaryTree();
    testBinaryTreeIterator();



    std::cout << "All tests passed!" << std::endl;
    std::initializer_list<int> lst = {5,4,7,2,6,9};
    BinaryTree<int> b(lst);
    std::string dotFilename = "graph";
    Vector<int> a(4);
    a.setElem(0,1);
    a.setElem(1,99);
    a.setElem(2,3);
    a.setElem(3,4);
    //a.generateGraphViz(dotFilename);
    //a.showGraph(dotFilename);
    b.generateGraphViz(dotFilename);
    b.showGraph(dotFilename);
    return 0;
}

