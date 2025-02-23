#include "circle.h"
#include <cmath>
Circle::Circle(Vertex center, double radius, std::string name):Shape(name) {
    this->center = center;
    this->radius = radius;
    if (radius <= 0)
        throw InvalidParameterException("radius must be larger than 0");
}

double Circle::getSquare() const {
    return acos(-1) * radius * radius;
}

