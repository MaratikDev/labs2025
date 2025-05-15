#ifndef VERTEX_H
#define VERTEX_H

#include "Point3D.h"
#include "sceneobject.h"
class Vertex : SceneObject
{
public:
    Vertex(point3D pos);
    point3D getPosition();
    void transform(TransformMatrix mat) override;
private:
    point3D position;
};

#endif // VERTEX_H
