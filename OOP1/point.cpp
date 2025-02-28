#include "Point.h"

Point::Point() {}

Point::Point(double xCoordinate, double yCoordinate) {
    this->xCoordinate = xCoordinate;
    this->yCoordinate = yCoordinate;
}

double Point::getXCoordinate() {
    return this->xCoordinate;
}

double Point::getYCoordinate() {
    return this->yCoordinate;
}
std::ostream& operator << (std::ostream& os, const Point& point){
    os << "x = ";
    os << point.xCoordinate << ", ";
    os << "y = ";
    os << point.yCoordinate << " ";
    return os;
}
std::istream& operator >> (std::istream& is, Point& point) {
    is >> point.xCoordinate >> point.yCoordinate;
    return is;
}
