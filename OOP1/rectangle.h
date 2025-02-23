#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"
#include "Vertex.h"
class Rectangle : public Shape {
public:
    Rectangle(Vertex firstVertex, Vertex secondVertex, std::string name);
    double getSquare() const override;
    friend std::ostream& operator << (std::ostream& os, const Rectangle& rectangle){
        os << "Type = Rectangle, ";
        os << "Name = " << rectangle.name;
        os << ", Left upper vertex: " << rectangle.vertex[0];
        os << ", Right under vertex: " << rectangle.vertex[1];
        return os;
    }
    void print(std::ostream& os) const override {
        os << *this;
    }

private:
    Vertex vertex[2];
};

#endif // RECTANGLE_H
