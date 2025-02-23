#ifndef CONSOLEAPP_H
#define CONSOLEAPP_H

#include <vector>
#include "Shape.h"

enum class Options {
    AddShape = 1,
    PrintAll,
    PrintAllAndSquares,
    SumSquare,
    Sorting,
    DeleteIndex,
    DeleteSquare
};

enum class OptionsShape {
    Circle = 1,
    Rectangle,
    Triangle
};

class ConsoleApp {
public:
    void addShape(Shape* shape);
    void printAllShapesInfo();
    void printAllShapesInfoAndSquare();
    void printSumOfSquares();
    void sortShapes();
    void deleteShapeByIndex(int index);
    void deleteShapesbySquare(double squareSize);
    void createCircle();
    void createTriangle();
    void createRectangle();
    void secondChoise();
    void firstChoise();
    void startApp();

private:
    std::vector<Shape*> arrOfShapes;
};

#endif // CONSOLEAPP_H
