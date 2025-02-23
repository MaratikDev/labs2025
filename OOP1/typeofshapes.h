#ifndef TYPEOFSHAPES_H
#define TYPEOFSHAPES_H

#include "Shape.h"
#include "Vertex.h"

// Класс Circle
class Circle : public Shape {
public:
    Circle(Vertex center, double radius);
    void getInfoAboutShape() const override;
    void getInfoAboutShapeAndSquare() const override;
    double getSquare() const override;

private:
    std::string name = "Circle";
    Vertex center;
    double radius;
};

// Класс Rectangle
class Rectangle : public Shape {
public:
    Rectangle(Vertex firstVertex, Vertex secondVertex);
    void getInfoAboutShape() const override;
    void getInfoAboutShapeAndSquare() const override;
    double getSquare() const override;

private:
    std::string name = "Rectangle";
    Vertex vertex[2];
};

// Класс Triangle
class Triangle : public Shape {
public:
    Triangle(Vertex firstVertex, Vertex secondVertex, Vertex thirdVertex);
    void getInfoAboutShape() const override;
    void getInfoAboutShapeAndSquare() const override;
    double getSquare() const override;

private:
    std::string name = "Triangle";
    Vertex vertex[3];
};

#endif // TYPEOFSHAPES_H
