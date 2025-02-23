#ifndef VERTEX_H
#define VERTEX_H
#include <iostream>
class Vertex {
public:
    Vertex();
    Vertex(double xCoordinate, double yCoordinate);

    double getXCoordinate();
    double getYCoordinate();
    friend std::ostream& operator << (std::ostream& os, const Vertex& vertex){
        os << "x = ";
        os << vertex.xCoordinate << ", ";
        os << "y = ";
        os << vertex.yCoordinate << " ";
        return os;
    }

private:
    double xCoordinate = 0;
    double yCoordinate = 0;
};

#endif // VERTEX_H
