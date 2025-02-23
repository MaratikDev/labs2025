#include "ConsoleApp.h"
#include "typeofshapes.h"
#include <iostream>
#include <algorithm>

void ConsoleApp::addShape(Shape* shape) {
    arrOfShapes.push_back(shape);
}

void ConsoleApp::printAllShapesInfo() {
    for (int i = 0; i < arrOfShapes.size(); i++) {
        std::cout << i+1 << " ";
        arrOfShapes[i]->getInfoAboutShape();
    }
}

void ConsoleApp::printAllShapesInfoAndSquare() {
    for (int i = 0; i < arrOfShapes.size(); i++) {
        std::cout << i+1 << " ";
        arrOfShapes[i]->getInfoAboutShapeAndSquare();
    }
}

void ConsoleApp::printSumOfSquares() {
    double sum = 0;
    for (int i = 0; i < arrOfShapes.size(); i++) {
        sum += arrOfShapes[i]->getSquare();
    }
    std::cout << sum;
}

void ConsoleApp::sortShapes() {
    std::sort(arrOfShapes.begin(), arrOfShapes.end(), [](Shape* a, Shape* b) {
        return a->getSquare() < b->getSquare();
    });
}

void ConsoleApp::deleteShapeByIndex(int index) {
    arrOfShapes.erase(arrOfShapes.begin() + index);
}

void ConsoleApp::deleteShapesbySquare(double squareSize) {
    for (int i = 0; i < arrOfShapes.size(); i++) {
        if (arrOfShapes[i]->getSquare() > squareSize) {
            deleteShapeByIndex(i);
            i--;
        }
    }
}

void ConsoleApp::createCircle() {
    double centerX;
    double centerY;
    double radius;
    std::cout << "Input coordinates of center and radius: ";
    std::cin >> centerX >> centerY >> radius;
    addShape(new Circle(Vertex(centerX, centerY), radius));
}

void ConsoleApp::createTriangle() {
    double vertex1X;
    double vertex1Y;
    double vertex2X;
    double vertex2Y;
    double vertex3X;
    double vertex3Y;
    std::cout << "Input coordinates of vertexes: ";
    std::cin >> vertex1X >> vertex1Y >> vertex2X >> vertex2Y >> vertex3X >> vertex3Y;
    addShape(new Triangle(Vertex(vertex1X, vertex1Y), Vertex(vertex2X, vertex2Y), Vertex(vertex3X, vertex3Y)));
}

void ConsoleApp::createRectangle() {
    double leftUpperVertexX;
    double leftUpperVertexY;
    double rightUppervertexX;
    double rightUppervertexY;
    std::cout << "Input coordinates of vertexes: leftUpperVertex, rightUppervertex : ";
    std::cin >> leftUpperVertexX >> leftUpperVertexY >> rightUppervertexX >> rightUppervertexY;
    addShape(new Rectangle(Vertex(leftUpperVertexX, leftUpperVertexY), Vertex(rightUppervertexX, rightUppervertexY)));
}

void ConsoleApp::secondChoise() {
    int choise;
    std::cout << "Input number:\n";
    std::cout << "1: Circle\n";
    std::cout << "2: Rectangle\n";
    std::cout << "3: Triangle\n";
    std::cin >> choise;
    if (choise < 1 || choise > 3)
        throw "XD";
    OptionsShape selectedOption = static_cast<OptionsShape>(choise);
    switch (selectedOption)
    {
    case OptionsShape::Circle:
        createCircle();
        break;
    case OptionsShape::Rectangle:
        createRectangle();
        break;
    case OptionsShape::Triangle:
        createTriangle();
        break;
    default:
        break;
    }
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
    std::cout << "7:Delete shape if its square larger than input number\n";
    std::cin >> choise;
    if (choise < 1 || choise >7)
        throw "XD";
    Options selectedOption = static_cast<Options>(choise);
    switch (selectedOption)
    {
    case Options::AddShape:
        secondChoise();
        break;
    case Options::PrintAll:
        printAllShapesInfo();
        break;
    case Options::PrintAllAndSquares:
        printAllShapesInfoAndSquare();
        break;
    case Options::SumSquare:
        printSumOfSquares();
        break;
    case Options::Sorting:
        sortShapes();
        break;
    case Options::DeleteIndex:
        int index;
        std::cout << "Input Index:\n";
        std::cin >> index;
        deleteShapeByIndex(index);
        break;
    case Options::DeleteSquare:
        double square;
        std::cout << "Input max square:\n";
        std::cin >> square;
        deleteShapesbySquare(square);
        break;
    default:
        break;
    }
}

void ConsoleApp::startApp() {
    while (true) {
        firstChoise();
    }
}
