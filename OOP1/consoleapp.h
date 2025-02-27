#ifndef CONSOLEAPP_H
#define CONSOLEAPP_H

#include <vector>
#include "Shape.h"
#include <map>
#include <functional>

class ConsoleApp {
public:
    ConsoleApp();
    void addShape(Shape* shape);
    void printAllShapesInfo();
    void printAllShapesInfoAndSquare();
    void printSumOfSquares();
    void sortShapes();
    void deleteShapeByIndex();
    void deleteShapesbySquare();
    void createCircle();
    void createTriangle();
    void createRectangle();
    void secondChoise();
    void firstChoise();
    void startApp();
    void initializeMethodsOfShapesMap();
    void initializeMethodsOfChoisesMap();
    void stopProgram();
private:
    std::vector<Shape*> arrOfShapes;
    std::map<int, std::function<void()>> methodsOfShapesMap;
    std::map<int, std::function<void()>> methodsOfChoisesMap;
    int flag;
};

#endif // CONSOLEAPP_H
