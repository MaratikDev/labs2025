#ifndef POINT_H
#define POINT_H
#include <iostream>
class Point {
public:
    Point();
    Point(double xCoordinate, double yCoordinate);

    double getXCoordinate();
    double getYCoordinate();
    friend std::ostream& operator << (std::ostream& os, const Point& point);
    friend std::istream& operator >> (std::istream& is, Point& point);
private:
    double xCoordinate;
    double yCoordinate;
};

#endif // POINT_H
