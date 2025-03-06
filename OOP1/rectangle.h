#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"
#include "Point.h"
#define COUNT_OF_RECTANGLE_POINTS 2
class Rectangle : public Shape {
public:
    Rectangle(Point firstVertex, Point secondVertex, std::string name);
    double getSquare() const override;
    void printInfo() const override;
    friend std::ostream& operator << (std::ostream& os, const Rectangle& rectangle);
    void print(std::ostream& os) const override;

private:
    Point point[COUNT_OF_RECTANGLE_POINTS];
};

#endif // RECTANGLE_H
