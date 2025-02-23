#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"
#include "Vertex.h"
#include <iostream>
class Circle : public Shape {
public:
    Circle(Vertex center, double radius, std::string name);
    double getSquare() const override;
    friend std::ostream& operator << (std::ostream& os, const Circle& circle){
        os << "Type = Circle, ";
        os << "Name = " << circle.name;
        os << ", Center: " << circle.center;
        os << ", Radius = " << circle.radius << std::endl;
        return os;
    }
    void print(std::ostream& os) const override {
        os << *this;
    }

private:
    Vertex center;
    double radius;
};

#endif // CIRCLE_H
