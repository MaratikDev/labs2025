#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"
#include "Vertex.h"
class Rectangle : public Shape {
public:
    Rectangle(Vertex firstVertex, Vertex secondVertex, std::string name);
    double getSquare() const override;
    void printInfo() const override;
    friend std::ostream& operator << (std::ostream& os, const Rectangle& rectangle){
        os << "Type = Rectangle, ";
        return os;
    }
    void print(std::ostream& os) const override {
        os << *this;
    }

private:
    Vertex vertex[2];
};

#endif // RECTANGLE_H
