#ifndef CONSOLEAPP_H
#define CONSOLEAPP_H

#include <vector>
#include "Shape.h"
#include <map>
#include <functional>

enum RunStatus {
    Stop,
    Running
};

class ConsoleApp {
public:
    ConsoleApp();
    void startApp();
    void stopProgram();
private:
    std::vector<Shape*> arrOfShapes;
    std::map<int, void (ConsoleApp::*)()> methodsOfShapesMap;
    std::map<int, void (ConsoleApp::*)()> methodsOfChoisesMap;
    RunStatus isRunning;
    void addShape(Shape* shape);
    void printAllShapesInfo();
    void printAllShapesInfoAndSquare();
    void printSumOfSquares();
    void sortShapes();
    void deleteShapeByIndex();
    void deleteShapesbySquare();
    void createPolygon();
    void createCircle();
    void createTriangle();
    void createRectangle();
    void secondChoise();
    void firstChoise();
    void initializeMethodsOfShapesMap();
    void initializeMethodsOfChoisesMap();
};

#endif // CONSOLEAPP_H
