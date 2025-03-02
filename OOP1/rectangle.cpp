#include "rectangle.h"
#include <cmath>
Rectangle::Rectangle(Point firstVertex, Point secondVertex, std::string name):Shape(name) {
    this->point[0] = firstVertex;
    this->point[1] = secondVertex;
    if ((this->getSquare() <= 0) || (point[0].getXCoordinate() > point[1].getXCoordinate()) || (point[0].getYCoordinate() < point[1].getYCoordinate()))
        throw InvalidParameterException("Its not a rectangle!!! Or you cant read instruction))");
}

double Rectangle::getSquare() const {
    Rectangle temp = *this;
    return abs((temp.point[0].getXCoordinate() - temp.point[1].getXCoordinate()) * (temp.point[0].getXCoordinate() - temp.point[1].getXCoordinate()));
}
void Rectangle::printInfo() const{
    std::cout << "Name = " << this->name << ", Left upper Point: " << this->point[0] << ", Right under Point: " << this->point[1] << std::endl;
}
