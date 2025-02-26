#include "triangle.h"
#include <cmath>
Triangle::Triangle(Vertex firstVertex, Vertex secondVertex, Vertex thirdVertex, std::string name):Shape(name) {
    this->vertex[0] = firstVertex;
    this->vertex[1] = secondVertex;
    this->vertex[2] = thirdVertex;
    if (this->getSquare() <= 0)
        throw InvalidParameterException("Its not a triangle!!!");
}

double Triangle::getSquare() const {
    Triangle temp = *this;
    return 0.5 * abs(
               (temp.vertex[1].getXCoordinate() - temp.vertex[0].getXCoordinate()) * (temp.vertex[2].getYCoordinate() - temp.vertex[0].getYCoordinate()) -
               (temp.vertex[2].getXCoordinate() - temp.vertex[0].getXCoordinate()) * (temp.vertex[1].getYCoordinate() - temp.vertex[0].getYCoordinate())
               );
}
void Triangle::printInfo() const{
    std::cout << "Name = " << this->name;
    for(int i = 0; i < 3; i++){
        std::cout << ", Vertex " << i+1 << ": ";
        std::cout << this->vertex[i];
    }
}
