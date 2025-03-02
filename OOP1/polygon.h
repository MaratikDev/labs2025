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
    friend std::ostream& operator << (std::ostream& os, const Polygon& triangle){
        os << "Type = Polygon, ";
        return os;
    }
    void print(std::ostream& os) const override {
        os << *this;
    }

private:
    Point* point;
    int countOfPoints;

    bool isConvex() const;
    static double vectorMultiply(const Point& a, const Point& b, const Point& c);
};

#endif // POLYGON_H
