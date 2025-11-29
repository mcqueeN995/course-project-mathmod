#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <stdexcept>

class Edge {
private:
    int fromId;
    int toId;
    double weight;
    bool isDirected;

public:
    Edge();
    Edge(int fromId, int toId, double weight = 1.0, bool isDirected = false);
    int getFromId() const;
    int getToId() const;
    double getWeight() const;
    bool getIsDirected() const;
    void setFromId(int fromId);
    void setToId(int toId);
    void setWeight(double weight);
    void setIsDirected(bool directed);
    friend std::ostream& operator<<(std::ostream& os, const Edge& edge);
    friend std::istream& operator>>(std::istream& is, Edge& edge);
};

#endif // EDGE_H
