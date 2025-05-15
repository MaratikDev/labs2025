#ifndef FIGURE_H
#define FIGURE_H

#include "edge.h"
#include "vertex.h"
#include <vector>
#include "sceneobject.h"

class Figure : public SceneObject
{
public:
    Figure(std::vector<Vertex> vertices);
    std::vector<Vertex> getVertices();
    std::vector<Edge> getEdges();
    void transform(TransformMatrix mat) override;
private:
    std::vector<Vertex> originalVertices;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
};

#endif // FIGURE_H
