#ifndef POLYGON_H
#define POLYGON_H

#include "Shape.h"
#include "Point.h"
#define COUNT_OF_TRIANGLE_POINTS 3
class Polygon : public Shape {
public:
    Polygon(int countOfPoints, std::string name);
    double getSquare() const override;
    void printInfo() const override;
    friend std::ostream& operator << (std::ostream& os, const Polygon& triangle);
    void print(std::ostream& os) const override;

private:
    Point* point;
    int countOfPoints;

    bool isConvex() const;
    static double vectorMultiply( Point& a,  Point& b,  Point& c) ;
};

#endif // POLYGON_H
