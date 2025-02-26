#include "ConsoleApp.h"
#include <iostream>
#include <algorithm>
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

void ConsoleApp::initializeMethodsOfShapesMap() {
    methodsOfShapesMap[1] = [this]() { this->createCircle(); };
    methodsOfShapesMap[2] = [this]() { this->createRectangle(); };
    methodsOfShapesMap[3] = [this]() { this->createTriangle(); };
}

void ConsoleApp::initializeMethodsOfChoisesMap(){
    methodsOfChoisesMap[1] = [this]() { this->secondChoise(); };
    methodsOfChoisesMap[2] = [this]() { this->printAllShapesInfo(); };
    methodsOfChoisesMap[3] = [this]() { this->printAllShapesInfoAndSquare(); };
    methodsOfChoisesMap[4] = [this]() { this->printSumOfSquares(); };
    methodsOfChoisesMap[5] = [this]() { this->sortShapes(); };
    methodsOfChoisesMap[6] = [this]() { this->deleteShapeByIndex(); };
    methodsOfChoisesMap[7] = [this]() { this->deleteShapesbySquare(); };
    methodsOfChoisesMap[8] = [this]() { this->stopProgram(); };
}

void ConsoleApp::stopProgram(){
    this->flag = 0;
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
    for (int i = 0; i < arrOfShapes.size(); i++) {
        sum += arrOfShapes[i]->getSquare();
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
    arrOfShapes.erase(arrOfShapes.begin() + index);
}

void ConsoleApp::deleteShapesbySquare() {
    double squareSize;
    std::cout << "Input max square:\n";
    std::cin >> squareSize;
    for (int i = 0; i < arrOfShapes.size(); i++) {
        if (arrOfShapes[i]->getSquare() > squareSize) {
            arrOfShapes.erase(arrOfShapes.begin() + i);
            i--;
        }
    }
}

void ConsoleApp::createCircle() {
    double centerX;
    double centerY;
    double radius;
    std::string name;
    std::cout << "Input name and coordinates of center and radius: ";
    std::cin >> name >> centerX >> centerY >> radius;
    addShape(new Circle(Vertex(centerX, centerY), radius, name));
}

void ConsoleApp::createTriangle() {
    double vertex1X;
    double vertex1Y;
    double vertex2X;
    double vertex2Y;
    double vertex3X;
    double vertex3Y;
    std::string name;
    std::cout << "Input name and coordinates of vertexes: ";
    std::cin >> name >>  vertex1X >> vertex1Y >> vertex2X >> vertex2Y >> vertex3X >> vertex3Y;
    addShape(new Triangle(Vertex(vertex1X, vertex1Y), Vertex(vertex2X, vertex2Y), Vertex(vertex3X, vertex3Y), name));
}

void ConsoleApp::createRectangle() {
    double leftUpperVertexX;
    double leftUpperVertexY;
    double rightUppervertexX;
    double rightUppervertexY;
    std::string name;
    std::cout << "Input name and coordinates of vertexes: leftUpperVertex, rightUppervertex : ";
    std::cin >> name >> leftUpperVertexX >> leftUpperVertexY >> rightUppervertexX >> rightUppervertexY;
    addShape(new Rectangle(Vertex(leftUpperVertexX, leftUpperVertexY), Vertex(rightUppervertexX, rightUppervertexY), name));
}

void ConsoleApp::secondChoise() {
    int choise;
    std::cout << "Input number:\n";
    std::cout << "1: Circle\n";
    std::cout << "2: Rectangle\n";
    std::cout << "3: Triangle\n";
    std::cin >> choise;
    if (choise < 1 || choise > 3)
        throw InvalidChoiceException("There are only 3 numbers). Pls choose one");
    auto it = methodsOfShapesMap.find(choise);
    it->second();
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
    if (choise < 1 || choise > 8)
        throw InvalidChoiceException("There are only 8 numbers). Pls choose one");
    auto it = methodsOfChoisesMap.find(choise);
    it->second();

}

void ConsoleApp::startApp() {
    initializeMethodsOfChoisesMap();
    initializeMethodsOfShapesMap();
    flag = 1;
    while (flag) {
        try {
            firstChoise();
        } catch (const InvalidChoiceException& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const InvalidParameterException& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Unexpected error: " << e.what() << std::endl;
        }
    }
}
