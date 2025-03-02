cmake_minimum_required(VERSION 3.16)

project(OOP1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OOP1 main.cpp
    point.h point.cpp
    shape.h

    consoleapp.h consoleapp.cpp
    circle.h circle.cpp
    rectangle.h rectangle.cpp
    triangle.h triangle.cpp
    shape.cpp
    exceptions.h
    polygon.h polygon.cpp )

include(GNUInstallDirs)
install(TARGETS OOP1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
