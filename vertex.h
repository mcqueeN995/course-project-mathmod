#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <string>
#include <stdexcept>

class Vertex {
private:
    int id;
    std::string label;
    double weight;

public:
    Vertex();
    Vertex(int id, const std::string& label, double weight = 0.0);
    int getId() const;
    std::string getLabel() const;
    double getWeight() const;
    void setId(int id);
    void setLabel(const std::string& label);
    void setWeight(double weight);
    friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex);
    friend std::istream& operator>>(std::istream& is, Vertex& vertex);
};

#endif // VERTEX_H
