#ifndef SHAPE_H
#define SHAPE_H
#include "exceptions.h"
#include <string>

class Shape {
public:
    Shape(std::string name);
    virtual void printInfo() const = 0;
    virtual double getSquare() const = 0;
    virtual void print(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Shape& shape);
    std::string getName() const;
private:
    std::string name;
};

#endif // SHAPE_H
