#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"
#include "Point.h"
#define COUNT_OF_TRIANGLE_POINTS 3
class Triangle : public Shape {
public:
    Triangle(Point firstVertex, Point secondVertex, Point thirdVertex, std::string name);
    double getSquare() const override;
    void printInfo() const override;
    friend std::ostream& operator << (std::ostream& os, const Triangle& triangle);
    void print(std::ostream& os) const override;

private:
    Point point[COUNT_OF_TRIANGLE_POINTS];
};

#endif // TRIANGLE_H
