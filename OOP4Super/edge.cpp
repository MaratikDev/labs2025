#include "edge.h"

Edge::Edge(Vertex v1, Vertex v2) : begin(v1), end(v2) {}

Vertex Edge::getBegin() { return begin; }
Vertex Edge::getEnd() { return end; }
