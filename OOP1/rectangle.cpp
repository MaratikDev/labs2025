#include "rectangle.h"
#include <cmath>
Rectangle::Rectangle(Vertex firstVertex, Vertex secondVertex, std::string name):Shape(name) {
    this->vertex[0] = firstVertex;
    this->vertex[1] = secondVertex;
    if (this->getSquare() <= 0)
        throw InvalidParameterException("Its not a rectangle!!!");
}

double Rectangle::getSquare() const {
    Rectangle temp = *this;
    return abs((temp.vertex[0].getXCoordinate() - temp.vertex[1].getXCoordinate()) * (temp.vertex[0].getXCoordinate() - temp.vertex[1].getXCoordinate()));
}
