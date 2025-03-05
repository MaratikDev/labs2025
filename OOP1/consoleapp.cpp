#include "ConsoleApp.h"
#include <iostream>
#include <ios>
#include <limits>
#include <algorithm>
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include "polygon.h"
#define MIN_CHOISE_FIRST 1
#define MAX_CHOISE_FIRST 8
#define MIN_CHOISE_SECOND 1
#define MAX_CHOISE_SECOND 4

ConsoleApp::ConsoleApp(){
    initializeMethodsOfChoisesMap();
    initializeMethodsOfShapesMap();
}

void ConsoleApp::initializeMethodsOfShapesMap() {
    methodsOfShapesMap[1] = &ConsoleApp::createCircle;
    methodsOfShapesMap[2] = &ConsoleApp::createRectangle;
    methodsOfShapesMap[3] = &ConsoleApp::createTriangle;
    methodsOfShapesMap[4] = &ConsoleApp::createPolygon;
}

void ConsoleApp::initializeMethodsOfChoisesMap(){
    methodsOfChoisesMap[1] = &ConsoleApp::secondChoise;
    methodsOfChoisesMap[2] = &ConsoleApp::printAllShapesInfo;
    methodsOfChoisesMap[3] = &ConsoleApp::printAllShapesInfoAndSquare;
    methodsOfChoisesMap[4] = &ConsoleApp::printSumOfSquares;
    methodsOfChoisesMap[5] = &ConsoleApp::sortShapes;
    methodsOfChoisesMap[6] = &ConsoleApp::deleteShapeByIndex;
    methodsOfChoisesMap[7] = &ConsoleApp::deleteShapesbySquare;
    methodsOfChoisesMap[8] = &ConsoleApp::stopProgram;
}

void ConsoleApp::stopProgram(){
    this->isRunning = Stop;
}

void ConsoleApp::addShape(Shape* shape) {
    arrOfShapes.push_back(shape);
}

void ConsoleApp::printAllShapesInfo() {
    for (int i = 0; i < arrOfShapes.size(); i++) {
        std::cout << i+1 << ": ";
        std::cout << *arrOfShapes[i];
        arrOfShapes[i]->printInfo();
    }
}

void ConsoleApp::printAllShapesInfoAndSquare() {
    for (int i = 0; i < arrOfShapes.size(); i++) {
        std::cout << i+1 << " ";
        std::cout << *arrOfShapes[i] << "Square = " << arrOfShapes[i]->getSquare() << std::endl;
    }
}

void ConsoleApp::printSumOfSquares() {
    double sum = 0;
    for (Shape* i : arrOfShapes) {
        sum += i->getSquare();
    }
    std::cout << sum << std::endl;
}

void ConsoleApp::sortShapes() {
    std::sort(arrOfShapes.begin(), arrOfShapes.end(), [](Shape* a, Shape* b) {
        return a->getSquare() < b->getSquare();
    });
}

void ConsoleApp::deleteShapeByIndex() {
    int index;
    std::cout << "Input Index:\n";
    std::cin >> index;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (index < 0 || index > arrOfShapes.size())
        throw InvalidChoiceException("Invalid index");
    arrOfShapes.erase(arrOfShapes.begin() + index);
}

void ConsoleApp::deleteShapesbySquare() {
    double squareSize;
    std::cout << "Input max square:\n";
    std::cin >> squareSize;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < arrOfShapes.size(); i++) {
        if (arrOfShapes[i]->getSquare() > squareSize) {
            arrOfShapes.erase(arrOfShapes.begin() + i);
            i--;
        }
    }
}

void ConsoleApp::createCircle() {
    Point center;
    double radius;
    std::string name;
    std::cout << "Input name and coordinates of center and radius: ";
    std::cin >> name;
    std::cin >> center;
    std::cin >> radius;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    addShape(new Circle(center, radius, name));
}

void ConsoleApp::createPolygon() {
    int countOfPoints;
    std::string name;
    std::cout << "Input name and count of points: ";
    std::cin >> name;
    std::cin >> countOfPoints;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    addShape(new Polygon(countOfPoints, name));
}

void ConsoleApp::createTriangle() {
    Point points[COUNT_OF_TRIANGLE_POINTS];
    std::string name;
    std::cout << "Input name and coordinates of vertexes: ";
    std::cin >> name;
    for(int i = 0; i < COUNT_OF_TRIANGLE_POINTS; i++){
        std::cin >> points[i];
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    addShape(new Triangle(points[0],points[1],points[2], name));
}

void ConsoleApp::createRectangle() {
    Point points[COUNT_OF_RECTANGLE_POINTS];
    std::string name;
    std::cout << "Input name and coordinates of vertexes: leftUpperVertex, rightUppervertex : ";
    std::cin >> name;
    for(int i = 0; i < COUNT_OF_RECTANGLE_POINTS; i++){
        std::cin >> points[i];
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    addShape(new Rectangle(points[0],points[1], name));
}

void ConsoleApp::secondChoise() {
    int choise;
    std::cout << "Input number:\n";
    std::cout << "1: Circle\n";
    std::cout << "2: Rectangle\n";
    std::cout << "3: Triangle\n";
    std::cout << "4: Polygon\n";
    std::cin >> choise;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (choise < MIN_CHOISE_SECOND || choise > MAX_CHOISE_SECOND)
        throw InvalidChoiceException("There are only 3 numbers). Pls choose one");
    auto it = methodsOfShapesMap.find(choise);
    (this->*(it->second))();
}

void ConsoleApp::firstChoise() {
    int choise;
    std::cout << "Input number:\n";
    std::cout << "1: Add shape in collection\n";
    std::cout << "2: Print all shapes with parametrs\n";
    std::cout << "3: Print all shapes with parametrs and squares\n";
    std::cout << "4: Print sum of squares\n";
    std::cout << "5: Sort by square\n";
    std::cout << "6: Delete shape by index\n";
    std::cout << "7: Delete shape if its square larger than input number\n";
    std::cout << "8: End program\n";
    std::cin >> choise;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (choise < MIN_CHOISE_FIRST || choise > MAX_CHOISE_FIRST)
        throw InvalidChoiceException("There are only 8 numbers). Pls choose one");
    auto it = methodsOfChoisesMap.find(choise);
    (this->*(it->second))();

}

void ConsoleApp::startApp() {
    isRunning = Running;
    while (isRunning) {
        try {
            firstChoise();
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
