#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include "edge.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

class Graph {
private:
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;

public:
    Graph();
    void addVertex(const Vertex& vertex);
    void addEdge(const Edge& edge);
    void removeVertex(int id);
    void removeEdge(int fromId, int toId);
    Vertex* getVertex(int id);
    int getVertexCount() const;
    int getEdgeCount() const;
    void printGraph() const;
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
    friend std::istream& operator>>(std::istream& is, Graph& graph);
};

#endif // GRAPH_H
