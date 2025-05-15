#include "figure.h"
#include "qdebug.h"
#include "qlogging.h"

Figure::Figure(std::vector<Vertex> vertices) : originalVertices(vertices), vertices(vertices) {
    for (std::size_t i = 0; i < originalVertices.size() - 1; i++) {
        edges.push_back(Edge(vertices[i], vertices[i + 1]));
    }
    edges.push_back(Edge(vertices.back(), vertices.front()));
}

std::vector<Vertex> Figure::getVertices() { return vertices; }
std::vector<Edge> Figure::getEdges() { return edges; }

void Figure::transform(TransformMatrix mat) {
    vertices.clear();
    for (const auto& originalVertex : originalVertices) {
        Vertex transformedVertex = originalVertex;
        transformedVertex.transform(mat);
        vertices.push_back(transformedVertex);
    }
    edges.clear();
    for (std::size_t i = 0; i < vertices.size() - 1; i++) {
        edges.push_back(Edge(vertices[i], vertices[i + 1]));
    }
    edges.push_back(Edge(vertices.back(), vertices.front()));
}
