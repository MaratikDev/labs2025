#include "typeOfShapes.h"
#include <iostream>
#include <cmath>

// Реализация методов класса Circle
Circle::Circle(Vertex center, double radius) {
    this->center = center;
    this->radius = radius;
    if (radius <= 0)
        throw "radius must be larger than 0";
}

void Circle::getInfoAboutShape() const {
    Circle temp = *this;
    std::cout << name << " ";
    std::cout << "Center: " << "x = " << temp.center.getXCoordinate() << ", y = " << temp.center.getYCoordinate();
    std::cout << ", Radius = " << radius << std::endl;
}

void Circle::getInfoAboutShapeAndSquare() const {
    Circle temp = *this;
    std::cout << name << " ";
    std::cout << "Center: " << "x = " << temp.center.getXCoordinate() << ", y = " << temp.center.getYCoordinate();
    std::cout << ", Radius = " << radius << " Square = " << getSquare() << std::endl;
}

double Circle::getSquare() const {
    return acos(-1) * radius * radius;
}

// Реализация методов класса Rectangle
Rectangle::Rectangle(Vertex firstVertex, Vertex secondVertex) {
    this->vertex[0] = firstVertex;
    this->vertex[1] = secondVertex;
    if (this->getSquare() <= 0)
        throw "Its a DOT!!!";
}

void Rectangle::getInfoAboutShape() const {
    Rectangle temp = *this;
    std::cout << name << " ";
    std::cout << "Left Upper Vertex: " << "x = " << temp.vertex[0].getXCoordinate() << ", y = " << temp.vertex[0].getYCoordinate();
    std::cout << " Right Lower Vertex: " << "x = " << temp.vertex[1].getXCoordinate() << ", y = " << temp.vertex[1].getYCoordinate() << std::endl;
}

void Rectangle::getInfoAboutShapeAndSquare() const {
    Rectangle temp = *this;
    std::cout << name << " ";
    std::cout << "Left Upper Vertex: " << "x = " << temp.vertex[0].getXCoordinate() << ", y = " << temp.vertex[0].getYCoordinate();
    std::cout << " Right Lower Vertex: " << "x = " << temp.vertex[1].getXCoordinate() << ", y = " << temp.vertex[1].getYCoordinate() << " Square = " << getSquare() << std::endl;
}

double Rectangle::getSquare() const {
    Rectangle temp = *this;
    return abs((temp.vertex[0].getXCoordinate() - temp.vertex[1].getXCoordinate()) * (temp.vertex[0].getXCoordinate() - temp.vertex[1].getXCoordinate()));
}

// Реализация методов класса Triangle
Triangle::Triangle(Vertex firstVertex, Vertex secondVertex, Vertex thirdVertex) {
    this->vertex[0] = firstVertex;
    this->vertex[1] = secondVertex;
    this->vertex[2] = thirdVertex;
    if (this->getSquare() <= 0)
        throw "Its a DOT!!!";
}

void Triangle::getInfoAboutShape() const {
    Triangle temp = *this;
    std::cout << name << " ";
    std::cout << "First Vertex: " << "x = " << temp.vertex[0].getXCoordinate() << ", y = " << temp.vertex[0].getYCoordinate();
    std::cout << " Second Vertex: " << "x = " << temp.vertex[1].getXCoordinate() << ", y = " << temp.vertex[1].getYCoordinate();
    std::cout << " Third Vertex: " << "x = " << temp.vertex[2].getXCoordinate() << ", y = " << temp.vertex[2].getYCoordinate() << std::endl;
}

void Triangle::getInfoAboutShapeAndSquare() const {
    Triangle temp = *this;
    std::cout << name << " ";
    std::cout << "First Vertex: " << "x = " << temp.vertex[0].getXCoordinate() << ", y = " << temp.vertex[0].getYCoordinate();
    std::cout << " Second Vertex: " << "x = " << temp.vertex[1].getXCoordinate() << ", y = " << temp.vertex[1].getYCoordinate();
    std::cout << " Third Vertex: " << "x = " << temp.vertex[2].getXCoordinate() << ", y = " << temp.vertex[2].getYCoordinate() << " Square = " << getSquare() << std::endl;
}

double Triangle::getSquare() const {
    Triangle temp = *this;
    return 0.5 * abs(
               (temp.vertex[1].getXCoordinate() - temp.vertex[0].getXCoordinate()) * (temp.vertex[2].getYCoordinate() - temp.vertex[0].getYCoordinate()) -
               (temp.vertex[2].getXCoordinate() - temp.vertex[0].getXCoordinate()) * (temp.vertex[1].getYCoordinate() - temp.vertex[0].getYCoordinate())
               );
}
