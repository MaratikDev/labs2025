#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include "Vertex.h"

class Shape {
public:
    std::string name;
    virtual double getSquare() const = 0;
    virtual void getInfoAboutShape() const = 0;
    virtual void getInfoAboutShapeAndSquare() const = 0;
};

#endif // SHAPE_H
