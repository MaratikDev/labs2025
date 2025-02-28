#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"
#include "Point.h"
#include <iostream>
class Circle : public Shape {
public:
    Circle(Point center, double radius, std::string name);
    double getSquare() const override;
    void printInfo() const override;
    friend std::ostream& operator << (std::ostream& os, const Circle& circle){
        os << "Type = Circle, ";
        return os;
    }
    void print(std::ostream& os) const override {
        os << *this;
    }

private:
    Point center;
    double radius;
};

#endif // CIRCLE_H
