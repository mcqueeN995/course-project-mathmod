#include "graph.h"

Graph::Graph() : vertices(), edges() {}

void Graph::addVertex(const Vertex& vertex) {
    try {
        for (const auto& v : vertices) {
            if (v.getId() == vertex.getId()) {
                throw std::invalid_argument(
                    "Вершина с ID " + std::to_string(vertex.getId()) + " уже существует"
                );
            }
        }
        vertices.push_back(vertex);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка при добавлении вершины: " << e.what() << std::endl;
        throw;
    }
}

void Graph::addEdge(const Edge& edge) {
    try {
        bool fromExists = false;
        bool toExists = false;

        for (const auto& v : vertices) {
            if (v.getId() == edge.getFromId()) {
                fromExists = true;
            }
            if (v.getId() == edge.getToId()) {
                toExists = true;
            }
        }
        if (!fromExists) {
            throw std::invalid_argument(
                "Вершина-источник с ID " + std::to_string(edge.getFromId()) + " не найдена"
            );
        }
        if (!toExists) {
            throw std::invalid_argument(
                "Вершина-назначение с ID " + std::to_string(edge.getToId()) + " не найдена"
            );
        }
        for (const auto& e : edges) {
            if (e.getFromId() == edge.getFromId() &&
                e.getToId() == edge.getToId()) {
                throw std::invalid_argument("Такое ребро уже существует");
            }
        }
        edges.push_back(edge);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка при добавлении ребра: " << e.what() << std::endl;
        throw;
    }
}

void Graph::removeVertex(int id) {
    try {
        auto it = std::find_if(vertices.begin(), vertices.end(),
            [id](const Vertex& v) { return v.getId() == id; });
        if (it == vertices.end()) {
            throw std::invalid_argument(
                "Вершина с ID " + std::to_string(id) + " не найдена"
            );
        }
        vertices.erase(it);

        edges.erase(
            std::remove_if(edges.begin(), edges.end(),
                [id](const Edge& e) {
                    return e.getFromId() == id || e.getToId() == id;
                }),
            edges.end()
        );

    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка при удалении вершины: " << e.what() << std::endl;
        throw;
    }
}

void Graph::removeEdge(int fromId, int toId) {
    try {
        auto it = std::find_if(edges.begin(), edges.end(),
            [fromId, toId](const Edge& e) {
                return e.getFromId() == fromId && e.getToId() == toId;
            });
        if (it == edges.end()) {
            throw std::invalid_argument(
                "Ребро от " + std::to_string(fromId) +
                " к " + std::to_string(toId) + " не найдено"
            );
        }
        edges.erase(it);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка при удалении ребра: " << e.what() << std::endl;
        throw;
    }
}

Vertex* Graph::getVertex(int id) {
    try {
        for (auto& v : vertices) {
            if (v.getId() == id) {
                return &v;
            }
        }
        throw std::invalid_argument(
            "Вершина с ID " + std::to_string(id) + " не найдена"
        );
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка при получении вершины: " << e.what() << std::endl;
        return nullptr;
    }
}

int Graph::getVertexCount() const {
    return vertices.size();
}

int Graph::getEdgeCount() const {
    return edges.size();
}

void Graph::printGraph() const {
    std::cout << "\n=== ИНФОРМАЦИЯ О ГРАФЕ ===" << std::endl;
    std::cout << "Количество вершин: " << vertices.size() << std::endl;
    std::cout << "Количество рёбер: " << edges.size() << std::endl;

    std::cout << "\nВЕРШИНЫ:" << std::endl;
    for (const auto& v : vertices) {
        std::cout << "  " << v << std::endl;
    }

    std::cout << "\nРЕБРА:" << std::endl;
    for (const auto& e : edges) {
        std::cout << "  " << e << std::endl;
    }
    std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    try {
        os << graph.vertices.size() << std::endl;
        for (const auto& v : graph.vertices) {
            os << v.getId() << " " << v.getLabel() << " " << v.getWeight() << std::endl;
        }

        os << graph.edges.size() << std::endl;

        for (const auto& e : graph.edges) {
            os << e.getFromId() << " " << e.getToId() << " "
               << e.getWeight() << " " << (e.getIsDirected() ? 1 : 0) << std::endl;
        }

        if (!os) {
            throw std::ios_base::failure("Ошибка при выводе графа в поток");
        }

        return os;

    } catch (const std::ios_base::failure& e) {
        std::cerr << "Ошибка ввода/вывода: " << e.what() << std::endl;
        throw;
    } catch (const std::exception& e) {
        std::cerr << "Неожиданная ошибка при выводе графа: " << e.what() << std::endl;
        throw;
    }
}

std::istream& operator>>(std::istream& is, Graph& graph) {
    try {
        graph.vertices.clear();
        graph.edges.clear();

        int vertexCount;
        if (!(is >> vertexCount)) {
            throw std::invalid_argument("Не удалось прочитать количество вершин");
        }

        if (vertexCount < 0) {
            throw std::invalid_argument("Количество вершин не может быть отрицательным");
        }

        for (int i = 0; i < vertexCount; ++i) {
            try {
                Vertex v;
                is >> v;
                graph.vertices.push_back(v);
            } catch (const std::exception& e) {
                throw std::runtime_error(
                    "Ошибка при чтении вершины " + std::to_string(i) + ": " + std::string(e.what())
                );
            }
        }

        int edgeCount;
        if (!(is >> edgeCount)) {
            throw std::invalid_argument("Не удалось прочитать количество рёбер");
        }

        if (edgeCount < 0) {
            throw std::invalid_argument("Количество рёбер не может быть отрицательным");
        }

        for (int i = 0; i < edgeCount; ++i) {
            try {
                Edge e;
                is >> e;
                graph.edges.push_back(e);

            } catch (const std::exception& e) {
                throw std::runtime_error(
                    "Ошибка при чтении ребра " + std::to_string(i) + ": " + std::string(e.what())
                );
            }
        }

        return is;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка при вводе графа: " << e.what() << std::endl;
        is.setstate(std::ios_base::failbit);
        throw;
    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка при обработке данных графа: " << e.what() << std::endl;
        is.setstate(std::ios_base::failbit);
        throw;
    } catch (const std::exception& e) {
        std::cerr << "Неожиданная ошибка при вводе графа: " << e.what() << std::endl;
        is.setstate(std::ios_base::failbit);
        throw;
    }
}
