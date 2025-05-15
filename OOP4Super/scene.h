#ifndef SCENE_H
#define SCENE_H
#include "figure.h"
#include "TransformMatrix.h"
#include <vector>
class Scene
{
public:
    void addFigure(Figure& figure);
    std::vector<Figure>& getFigures();
    void transformFigures(TransformMatrix& matrix);
private:
    std::vector<Figure> figures;
};

#endif // SCENE_H
