#include "scene.h"



void Scene::addFigure(Figure& figure) {
    figures.push_back(figure);
}

void Scene::transformFigures(TransformMatrix& matrix) {
    for (auto& figure : figures) {
        figure.transform(matrix);
    }
}

std::vector<Figure> &Scene::getFigures(){
    return figures;
}
