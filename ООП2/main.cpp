#include <iostream>
#include "m_vector.h"
int main()
{


    m_vector<int>a (2);
    a.set_elem(0, 1);
    a.set_elem(1, 2);
     m_vector<int>b (4);
    b.set_elem(0, 2);
    b.set_elem(1, 4);
    b.set_elem(2, 6);
    b.set_elem(3,9);
    m_vector<int> c = a+b;  //3 6 6 9


    Iterator<int> iter = c.iterator_begin();
    while(!iter.is_end()){
        std::cout<<iter.value();
        std::cout<<"\n";
        iter.next();
    }



    //delete a;
    //delete b;
}




