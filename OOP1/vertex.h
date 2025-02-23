#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
public:
    Vertex();
    Vertex(double xCoordinate, double yCoordinate);

    double getXCoordinate();
    double getYCoordinate();

private:
    double xCoordinate = 0;
    double yCoordinate = 0;
};

#endif // VERTEX_H
