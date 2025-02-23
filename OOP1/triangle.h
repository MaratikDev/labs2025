#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"
#include "Vertex.h"
class Triangle : public Shape {
public:
    Triangle(Vertex firstVertex, Vertex secondVertex, Vertex thirdVertex, std::string name);
    double getSquare() const override;
    friend std::ostream& operator << (std::ostream& os, const Triangle& triangle){
        os << "Type = Triangle, ";
        os << "Name = " << triangle.name;
        for(int i = 0; i < 3; i++){
            os << ", Vertex " << i+1 << ": ";
            os << triangle.vertex[i];
        }
        return os;
    }
    void print(std::ostream& os) const override {
        os << *this;
    }

private:
    Vertex vertex[3];
};

#endif // TRIANGLE_H
