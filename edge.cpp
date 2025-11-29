#include "edge.h"
#include <iostream>
#include <stdexcept>

Edge::Edge() : fromId(0), toId(0), weight(1.0), isDirected(false) {}

Edge::Edge(int fromId, int toId, double weight, bool isDirected) : fromId(fromId), toId(toId), weight(weight), isDirected(isDirected) {
    if (fromId < 0) {
        throw std::invalid_argument("ID вершины-источника не может быть отрицательным");
    }

    if (toId < 0) {
        throw std::invalid_argument("ID вершины-назначения не может быть отрицательным");
    }

    if (fromId == toId) {
        throw std::invalid_argument("Самопетля недопустима");
    }

    if (weight <= 0) {
        throw std::invalid_argument("Вес ребра должен быть положительным числом");
    }
}

int Edge::getFromId() const {
    return fromId;
}

int Edge::getToId() const {
    return toId;
}

double Edge::getWeight() const {
    return weight;
}

bool Edge::getIsDirected() const {
    return isDirected;
}

void Edge::setFromId(int newFromId) {
    if (newFromId < 0) {
        throw std::invalid_argument("ID вершины-источника не может быть отрицательным");
    }
    if (newFromId == toId) {
        throw std::invalid_argument("Самопетля недопустима");
    }
    fromId = newFromId;
}

void Edge::setToId(int newToId) {
    if (newToId < 0) {
        throw std::invalid_argument("ID вершины-назначения не может быть отрицательным");
    }
    if (newToId == fromId) {
        throw std::invalid_argument("Самопетля недопустима");
    }
    toId = newToId;
}

void Edge::setWeight(double newWeight) {
    if (newWeight <= 0) {
        throw std::invalid_argument("Вес ребра должен быть положительным числом");
    }
    weight = newWeight;
}

void Edge::setIsDirected(bool directed) {
    isDirected = directed;
}

std::ostream& operator<<(std::ostream& os, const Edge& edge) {
    try {
        std::string separator = edge.isDirected ? " -> " : " -- ";
        std::string directedStr = edge.isDirected ? "yes" : "no";

        os << edge.fromId << separator << edge.toId
                << " (weight: " << edge.weight
                << ", directed: " << directedStr << ")";

        if (!os) {
            throw std::ios_base::failure("Ошибка при выводе ребра в поток");
        }

        return os;
    } catch (const std::ios_base::failure& e) {
        std::cerr << "Ошибка ввода/вывода: " << e.what() << std::endl;
        throw;
    }
}

std::istream& operator>>(std::istream& is, Edge& edge) {
    try {
        int tempFromId, tempToId;
        double tempWeight;
        int tempDirected;

        if (!(is >> tempFromId)) {
            throw std::invalid_argument("Не удалось прочитать ID вершины-источника");
        }

        if (!(is >> tempToId)) {
            throw std::invalid_argument("Не удалось прочитать ID вершины-назначения");
        }

        if (!(is >> tempWeight)) {
            throw std::invalid_argument("Не удалось прочитать вес ребра");
        }

        if (!(is >> tempDirected)) {
            throw std::invalid_argument("Не удалось прочитать флаг направленности");
        }

        if (tempFromId < 0) {
            throw std::invalid_argument("ID источника не может быть отрицательным");
        }

        if (tempToId < 0) {
            throw std::invalid_argument("ID назначения не может быть отрицательным");
        }

        if (tempFromId == tempToId) {
            throw std::invalid_argument("Самопетля недопустима");
        }

        if (tempWeight <= 0) {
            throw std::invalid_argument("Вес ребра должен быть положительным");
        }

        if (tempDirected != 0 && tempDirected != 1) {
            throw std::invalid_argument("Флаг направленности должен быть 0 или 1");
        }

        edge.fromId = tempFromId;
        edge.toId = tempToId;
        edge.weight = tempWeight;
        edge.isDirected = (tempDirected == 1);

        return is;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка при вводе ребра: " << e.what() << std::endl;
        is.setstate(std::ios_base::failbit);
        throw;
    } catch (const std::exception& e) {
        std::cerr << "Неожиданная ошибка при вводе ребра: " << e.what() << std::endl;
        is.setstate(std::ios_base::failbit);
        throw;
    }
}
