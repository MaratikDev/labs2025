#include "vertex.h"

Vertex::Vertex(point3D pos) : position(pos) {}

point3D Vertex::getPosition() { return position; }

void Vertex::transform(TransformMatrix matrix) {
    position = matrix.transformPoint(position);
}
