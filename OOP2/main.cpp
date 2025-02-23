#include <iostream>
#include <cassert>
#include "Vector.h"

void test_vector() {
    // Test constructor with initializer list
    std::initializer_list<int> lst = {1, 2, 3, 4};
    Vector<int> v1(lst);
    assert(v1.get_length() == 4);
    assert(v1[0] == 1);
    assert(v1[1] == 2);
    assert(v1[2] == 3);
    assert(v1[3] == 4);

    // Test copy constructor
    Vector<int> v2(v1);
    assert(v2.get_length() == 4);
    assert(v2[0] == 1);
    assert(v2[1] == 2);
    assert(v2[2] == 3);
    assert(v2[3] == 4);

    // Test assignment operator
    Vector<int> v3 = v1;
    assert(v3.get_length() == 4);
    assert(v3[0] == 1);
    assert(v3[1] == 2);
    assert(v3[2] == 3);
    assert(v3[3] == 4);

    // Test operator +=
    Vector<int> v4(lst);
    v4 += v1;
    assert(v4[0] == 2);
    assert(v4[1] == 4);
    assert(v4[2] == 6);
    assert(v4[3] == 8);

    // Test operator -=
    v4 -= v1;
    assert(v4[0] == 1);
    assert(v4[1] == 2);
    assert(v4[2] == 3);
    assert(v4[3] == 4);

    // Test operator *=
    v4 *= 2;
    assert(v4[0] == 2);
    assert(v4[1] == 4);
    assert(v4[2] == 6);
    assert(v4[3] == 8);

    // Test operator /=
    v4 /= 2;
    assert(v4[0] == 1);
    assert(v4[1] == 2);
    assert(v4[2] == 3);
    assert(v4[3] == 4);

    // Test to_array
    int* arr = v4.to_array();
    assert(arr[0] == 1);
    assert(arr[1] == 2);
    assert(arr[2] == 3);
    assert(arr[3] == 4);
    delete[] arr;

    std::cout << "All Vector tests passed!" << std::endl;
}

void test_iterator() {
    std::initializer_list<int> lst = {1, 2, 3, 4};
    Vector<int> v1(lst);

    // Test iterator begin and end
    Iterator<int> it = v1.iterator_begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 3);
    ++it;
    assert(*it == 4);
    ++it;
    assert(it.is_end());

    // Test iterator equality
    Iterator<int> it2 = v1.iterator_begin();
    Iterator<int> it3 = v1.iterator_begin();
    assert(it3 == it2);

    // Test iterator inequality
    ++it3;
    assert(it3 != it2);

    std::cout << "All Iterator tests passed!" << std::endl;
}

int main() {
    test_vector();
    test_iterator();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
