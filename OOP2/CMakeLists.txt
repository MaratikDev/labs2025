cmake_minimum_required(VERSION 3.16)

project(OOP2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OOP2 main.cpp


    Vector.h
    Iterator.h
    Vector.hpp
    Iterator.hpp
    BinaryTree.hpp
    BinaryTree.h
    IteratorBinTree.hpp
    IteratorBinTree.h
    TreeNode.h
    exceptions.h
    StaticTreeIterator.h
    StaticIterator.h
    StaticIterator.hpp




)

include(GNUInstallDirs)
install(TARGETS OOP2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
