#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include "edge.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <queue>
#include <map>

class Graph {
private:
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;

    void processEdge(int fromId, int toId, int fromPartition, std::map<int, int>& partition, std::queue<int>& bfsQueue, bool& isBipartiteGraph);
    bool dfsHelper(int vertexId, int color, std::map<int, int>& partition);

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
    bool isBipartite(std::map<int, int>& partition);
    bool isBipartiteDFS(std::map<int, int>& partition);
    void printBipartiteInfo(const std::map<int, int>& partition) const;
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
    friend std::istream& operator>>(std::istream& is, Graph& graph);
};

#endif // GRAPH_H
