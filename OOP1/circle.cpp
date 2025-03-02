#include "circle.h"
#include <cmath>
Circle::Circle(Point center, double radius, std::string name):Shape(name) {
    this->center = center;
    this->radius = radius;
    if (radius <= 0)
        throw InvalidParameterException("radius must be larger than 0");
}

double Circle::getSquare() const {
    return acos(-1) * radius * radius;
}
void Circle::printInfo() const{
    std::cout << "Name = " << this->name << ", Center: " << this->center << ", Radius = " << this->radius << std::endl;
}

