#include "polygon.h"

#include <cmath>
Polygon::Polygon(int countOfPoints, std::string name) : Shape(name), countOfPoints(countOfPoints) {
    if (countOfPoints < 3) {
        throw InvalidParameterException("Polygon must have at least 3 points ");
    }

    point = new Point[countOfPoints];
    std::cout << "Input " << countOfPoints <<" points: \n";
    for (int i = 0; i < countOfPoints; i++) {
        std::cin >> point[i];
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!isConvex()) {
        throw InvalidParameterException("Polygon is not convex ");
    }

    if (this->getSquare() <= 0) {
        throw InvalidParameterException("Invalid polygon: area is non-positive ");
    }
}


double Polygon::getSquare() const {
    double area = 0.0;
    for (int i = 0; i < countOfPoints; i++) {
        int j = (i + 1) % countOfPoints;
        area += (point[i].getXCoordinate() * point[j].getYCoordinate()) - (point[j].getXCoordinate() * point[i].getYCoordinate());
    }
    return std::abs(area) / 2.0;
}

void Polygon::printInfo() const {
    std::cout << "Name = " << this->getName();
    for (int i = 0; i < this->countOfPoints; i++) {
        std::cout << ", Point " << i + 1 << ": " << this->point[i];
    }
    std::cout << std::endl;
}


double Polygon::vectorMultiply( Point& a,  Point& b,  Point& c)  {
    return (b.getXCoordinate() - a.getXCoordinate()) * (c.getYCoordinate() - a.getYCoordinate()) -
           (b.getYCoordinate() - a.getYCoordinate()) * (c.getXCoordinate() - a.getXCoordinate());
}
std::ostream& operator << (std::ostream& os, const Polygon& triangle){
    os << "Type = Polygon, ";
    return os;
}
void Polygon::print(std::ostream& os) const {
    os << *this;
}

bool Polygon::isConvex() const {
    bool result = true;
    if (countOfPoints < 3)
        result = false;

    double initialSign = 0.0;
    for (int i = 0; i < countOfPoints; i++) {
        int j = (i + 1) % countOfPoints;
        int k = (i + 2) % countOfPoints;
        double cp = vectorMultiply(point[i], point[j], point[k]);
        if (cp == 0)
            result = false;
        if (initialSign == 0.0) {
            initialSign = cp;
        }
        else if (cp * initialSign < 0) {
            result = false;
        }
    }

    return result;
}
