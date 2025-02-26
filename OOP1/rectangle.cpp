#include "rectangle.h"
#include <cmath>
Rectangle::Rectangle(Vertex firstVertex, Vertex secondVertex, std::string name):Shape(name) {
    this->vertex[0] = firstVertex;
    this->vertex[1] = secondVertex;
    if ((this->getSquare() <= 0) || (vertex[0].getXCoordinate() > vertex[1].getXCoordinate()) || (vertex[0].getYCoordinate() < vertex[1].getYCoordinate()))
        throw InvalidParameterException("Its not a rectangle!!! Or you cant read instruction))");
}

double Rectangle::getSquare() const {
    Rectangle temp = *this;
    return abs((temp.vertex[0].getXCoordinate() - temp.vertex[1].getXCoordinate()) * (temp.vertex[0].getXCoordinate() - temp.vertex[1].getXCoordinate()));
}
void Rectangle::printInfo() const{
    std::cout << "Name = " << this->name;
    std::cout << ", Left upper vertex: " << this->vertex[0];
    std::cout << ", Right under vertex: " << this->vertex[1];
}
