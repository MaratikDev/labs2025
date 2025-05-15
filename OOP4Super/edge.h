#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

class Edge {
public:
    Edge(Vertex v1, Vertex v2);
    Vertex getBegin();
    Vertex getEnd();
private:
    Vertex begin;
    Vertex end;
};

#endif // EDGE_H
