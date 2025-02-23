#include "Vertex.h"

Vertex::Vertex() {}

Vertex::Vertex(double xCoordinate, double yCoordinate) {
    this->xCoordinate = xCoordinate;
    this->yCoordinate = yCoordinate;
}

double Vertex::getXCoordinate() {
    return this->xCoordinate;
}

double Vertex::getYCoordinate() {
    return this->yCoordinate;
}
