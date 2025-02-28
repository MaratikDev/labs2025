#include "triangle.h"
#include <cmath>
Triangle::Triangle(Point firstVertex, Point secondVertex, Point thirdVertex, std::string name):Shape(name) {
    this->point[0] = firstVertex;
    this->point[1] = secondVertex;
    this->point[2] = thirdVertex;
    if (this->getSquare() <= 0)
        throw InvalidParameterException("Its not a triangle!!!");
}

double Triangle::getSquare() const {
    Triangle temp = *this;
    return 0.5 * abs(
               (temp.point[1].getXCoordinate() - temp.point[0].getXCoordinate()) * (temp.point[2].getYCoordinate() - temp.point[0].getYCoordinate()) -
               (temp.point[2].getXCoordinate() - temp.point[0].getXCoordinate()) * (temp.point[1].getYCoordinate() - temp.point[0].getYCoordinate())
               );
}
void Triangle::printInfo() const{
    std::cout << "Name = " << this->name;
    for(int i = 0; i < 3; i++){
        std::cout << ", Point " << i+1 << ": ";
        std::cout << this->point[i];
    }
}
