#include "graph.h"
#include <iomanip>  // Добавляем для std::setw, std::setprecision
#include <sstream>  // Добавляем для std::istringstream
#include <limits>
#include <cmath>

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

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    try {
        if (graph.vertices.empty()) {
            if (&os == &std::cout || &os == &std::cerr) {
                os << "Граф пуст - матрица смежности отсутствует" << std::endl;
            }
            return os;
        }

        std::map<int, int> idToIndex;
        std::vector<int> indexToId;

        for (const auto& vertex : graph.vertices) {
            idToIndex[vertex.getId()] = indexToId.size();
            indexToId.push_back(vertex.getId());
        }

        int n = graph.vertices.size();

        std::vector<std::vector<double>> adjMatrix(n, std::vector<double>(n, 0.0));

        for (const auto& edge : graph.edges) {
            int fromIdx = idToIndex[edge.getFromId()];
            int toIdx = idToIndex[edge.getToId()];

            if (edge.getIsDirected()) {
                adjMatrix[fromIdx][toIdx] = edge.getWeight();
            } else {
                adjMatrix[fromIdx][toIdx] = edge.getWeight();
                adjMatrix[toIdx][fromIdx] = edge.getWeight();
            }
        }

        bool isConsole = (&os == &std::cout || &os == &std::cerr);

        if (isConsole) {
            os << "\n" << std::string(50, '=') << std::endl;
            os << "МАТРИЦА СМЕЖНОСТИ ГРАФА" << std::endl;
            os << std::string(50, '=') << std::endl;

            os << "     ";
            for (int i = 0; i < n; i++) {
                os << std::setw(4) << indexToId[i] << " ";
            }
            os << std::endl;

            os << "    ┌";
            for (int i = 0; i < n; i++) {
                os << "─────";
            }
            os << "┐" << std::endl;

            for (int i = 0; i < n; i++) {
                os << std::setw(3) << indexToId[i] << " │";
                for (int j = 0; j < n; j++) {
                    if (adjMatrix[i][j] == 0.0) {
                        os << "  ·  ";
                    } else {
                        os << std::setw(4) << std::fixed << std::setprecision(1)
                           << adjMatrix[i][j] << " ";
                    }
                }
                os << "│" << std::endl;
            }

            os << "    └";
            for (int i = 0; i < n; i++) {
                os << "─────";
            }
            os << "┘" << std::endl;

        } else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    os << adjMatrix[i][j];
                    if (j < n - 1) os << " ";
                }
                os << std::endl;
            }
        }

        if (!os) {
            throw std::ios_base::failure("Ошибка при выводе матрицы смежности");
        }

        return os;

    } catch (const std::ios_base::failure& e) {
        std::cerr << "Ошибка ввода/вывода: " << e.what() << std::endl;
        throw;
    } catch (const std::exception& e) {
        std::cerr << "Неожиданная ошибка при выводе матрицы: " << e.what() << std::endl;
        throw;
    }
}

std::istream& operator>>(std::istream& is, Graph& graph) {
    try {
        graph.vertices.clear();
        graph.edges.clear();
        std::vector<std::vector<double>> matrix;
        std::string line;

        while (std::getline(is, line)) {
            if (line.empty()) continue;

            std::vector<double> row;
            std::istringstream iss(line);
            double value;

            while (iss >> value) {
                row.push_back(value);
            }

            if (!row.empty()) {
                matrix.push_back(row);
            }
        }

        int n = matrix.size();
        if (n == 0) {
            return is;
        }

        for (const auto& row : matrix) {
            if (row.size() != n) {
                throw std::invalid_argument("Матрица смежности должна быть квадратной");
            }
        }

        for (int i = 1; i <= n; i++) {
            graph.vertices.push_back(Vertex(i, "V" + std::to_string(i), 1.0));
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] != 0.0) {
                    bool isDirected = (matrix[i][j] != matrix[j][i]);
                    graph.edges.push_back(Edge(i + 1, j + 1, matrix[i][j], isDirected));
                }
            }
        }

        return is;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка при вводе матрицы: " << e.what() << std::endl;
        is.setstate(std::ios_base::failbit);
        throw;
    } catch (const std::exception& e) {
        std::cerr << "Неожиданная ошибка при вводе матрицы: " << e.what() << std::endl;
        is.setstate(std::ios_base::failbit);
        throw;
    }
}

bool Graph::isBipartite(std::map<int, int>& partition) {
    try {
        partition.clear();
        for (const auto& v : vertices) {
            partition[v.getId()] = -1;
        }

        if (vertices.empty()) {
            std::cout << "Граф пуст. Это двудольный граф." << std::endl;
            return true;
        }

        bool isBipartiteGraph = true;

        for (const auto& startVertex : vertices) {
            int start = startVertex.getId();

            if (partition[start] != -1) {
                continue;
            }

            std::queue<int> bfsQueue;

            partition[start] = 0;

            bfsQueue.push(start);

            while (!bfsQueue.empty() && isBipartiteGraph) {
                int currentVertexId = bfsQueue.front();
                bfsQueue.pop();
                int currentPartition = partition[currentVertexId];
                for (const auto& edge : edges) {
                    if (edge.getFromId() == currentVertexId) {
                        int neighborId = edge.getToId();
                        this->processEdge(currentVertexId, neighborId, currentPartition,
                                         partition, bfsQueue, isBipartiteGraph);
                    }
                    else if (!edge.getIsDirected() && edge.getToId() == currentVertexId) {
                        int neighborId = edge.getFromId();
                        this->processEdge(currentVertexId, neighborId, currentPartition,
                                         partition, bfsQueue, isBipartiteGraph);
                    }
                }
            }
            if (!isBipartiteGraph) {
                break;
            }
        }

        return isBipartiteGraph;

    } catch (const std::exception& e) {
        std::cerr << "Ошибка при проверке двудольности: " << e.what() << std::endl;
        throw;
    }
}

void Graph::processEdge(int fromId, int toId, int fromPartition,
                        std::map<int, int>& partition,
                        std::queue<int>& bfsQueue,
                        bool& isBipartiteGraph) {
    if (partition[toId] == -1) {
        partition[toId] = !fromPartition;
        bfsQueue.push(toId);
    }
    else {
        if (partition[toId] == partition[fromId]) {
            std::cerr << "Обнаружено ребро между вершинами одной доли: "
                      << fromId << " (доля " << partition[fromId] << ") и "
                      << toId << " (доля " << partition[toId] << ")" << std::endl;
            isBipartiteGraph = false;
        }
    }
}

void Graph::printBipartiteInfo(const std::map<int, int>& partition) const {
    try {
        std::cout << "\n=== ИНФОРМАЦИЯ О ДВУДОЛЬНОСТИ ===" << std::endl;

        std::vector<int> part0, part1;

        for (const auto& [vertexId, partitionId] : partition) {
            if (partitionId == 0) {
                part0.push_back(vertexId);
            } else if (partitionId == 1) {
                part1.push_back(vertexId);
            }
        }

        std::cout << "Доля 0 (" << part0.size() << " вершин): ";
        for (int id : part0) {
            std::cout << id << " ";
        }
        std::cout << std::endl;

        std::cout << "Доля 1 (" << part1.size() << " вершин): ";
        for (int id : part1) {
            std::cout << id << " ";
        }
        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Ошибка при выводе информации о двудольности: " << e.what() << std::endl;
        throw;
    }
}

bool Graph::dfsHelper(int vertexId, int color, std::map<int, int>& partition) {
    try {
        partition[vertexId] = color;

        for (const auto& edge : edges) {
            int neighborId = -1;
            bool isNeighbor = false;

            if (edge.getFromId() == vertexId) {
                neighborId = edge.getToId();
                isNeighbor = true;
            }
            else if (!edge.getIsDirected() && edge.getToId() == vertexId) {
                neighborId = edge.getFromId();
                isNeighbor = true;
            }

            if (isNeighbor) {
                if (partition[neighborId] == -1) {
                    int nextColor = 1 - color;
                    if (!dfsHelper(neighborId, nextColor, partition)) {
                        return false;
                    }
                } else {
                    if (partition[neighborId] == partition[vertexId]) {
                        std::cerr << "Обнаружено ребро между вершинами одного цвета: "
                                  << vertexId << " (цвет " << partition[vertexId] << ") и "
                                  << neighborId << " (цвет " << partition[neighborId] << ")" << std::endl;
                        return false;
                    }
                }
            }
        }
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка в DFS: " << e.what() << std::endl;
        throw;
    }
}

bool Graph::isBipartiteDFS(std::map<int, int>& partition) {
    try {
        partition.clear();

        for (const auto& v : vertices) {
            partition[v.getId()] = -1;
        }


        if (vertices.empty()) {
            std::cout << "Граф пуст. Это двудольный граф." << std::endl;
            return true;
        }

        for (const auto& startVertex : vertices) {
            int startId = startVertex.getId();

            if (partition[startId] != -1) {
                continue;
            }

            std::cout << "Запуск DFS из вершины " << startId << std::endl;

            if (!dfsHelper(startId, 0, partition)) {
                std::cout << "Граф НЕ двудольный" << std::endl;
                return false;
            }
        }

        std::cout << "Граф успешно окрашен в два цвета" << std::endl;
        return true;

    } catch (const std::exception& e) {
        std::cerr << "Ошибка при проверке двудольности (DFS): " << e.what() << std::endl;
        throw;
    }
}

std::pair<double, std::vector<std::pair<int, int>>> Graph::solveAssignmentProblem(
    const std::vector<int>& firstPart,
    const std::vector<int>& secondPart) {

    try {
        const double INF = 1e9;
        int n = firstPart.size();

        if (n != secondPart.size()) {
            throw std::invalid_argument("Размеры долей должны быть одинаковыми");
        }

        if (n == 0) {
            return {0.0, {}};
        }

        std::vector<std::vector<double>> cost(n, std::vector<double>(n, INF));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int fromId = firstPart[i];
                int toId = secondPart[j];

                for (const auto& edge : edges) {
                    if ((edge.getFromId() == fromId && edge.getToId() == toId) ||
                        (!edge.getIsDirected() && edge.getFromId() == toId && edge.getToId() == fromId)) {
                        cost[i][j] = edge.getWeight();
                        break;
                    }
                }
            }
        }

        std::vector<double> u(n+1, 0), v(n+1, 0);
        std::vector<int> p(n+1, 0), way(n+1, 0);

        for (int i = 1; i <= n; i++) {
            p[0] = i;
            int j0 = 0;
            std::vector<double> minv(n+1, INF);
            std::vector<bool> used(n+1, false);

            do {
                used[j0] = true;
                int i0 = p[j0];
                double delta = INF;
                int j1 = 0;

                for (int j = 1; j <= n; j++) {
                    if (!used[j]) {
                        double cur = cost[i0-1][j-1] - u[i0] - v[j];
                        if (cur < minv[j]) {
                            minv[j] = cur;
                            way[j] = j0;
                        }
                        if (minv[j] < delta) {
                            delta = minv[j];
                            j1 = j;
                        }
                    }
                }

                for (int j = 0; j <= n; j++) {
                    if (used[j]) {
                        u[p[j]] += delta;
                        v[j] -= delta;
                    } else {
                        minv[j] -= delta;
                    }
                }

                j0 = j1;
            } while (p[j0] != 0);

            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }

        double totalCost = -v[0];
        std::vector<std::pair<int, int>> matching;

        for (int j = 1; j <= n; j++) {
            if (p[j] != 0) {
                matching.push_back({firstPart[p[j]-1], secondPart[j-1]});
            }
        }

        if (totalCost > INF / 2) {
            throw std::runtime_error("Не удалось найти совершенное паросочетание: возможно, граф не полный");
        }

        return {totalCost, matching};

    } catch (const std::exception& e) {
        std::cerr << "Ошибка в Венгерском алгоритме: " << e.what() << std::endl;
        throw;
    }
}

std::vector<std::pair<int, int>> Graph::findMaximumMatching() {
    try {
        for (const auto& edge : edges) {
            if (edge.getIsDirected()) {
                throw std::invalid_argument("Алгоритм Эдмондса работает только с неориентированными графами");
            }
        }

        if (vertices.empty()) {
            return {};
        }

        std::map<int, int> idToIndex;
        std::vector<int> indexToId;
        for (const auto& vertex : vertices) {
            idToIndex[vertex.getId()] = indexToId.size();
            indexToId.push_back(vertex.getId());
        }

        int n = vertices.size();

        std::vector<std::vector<int>> adj(n);
        for (const auto& edge : edges) {
            int u = idToIndex[edge.getFromId()];
            int v = idToIndex[edge.getToId()];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        std::vector<int> match(n, -1);
        std::vector<int> parent(n), base(n), color(n);

        auto lca = [&](int a, int b) {
            std::vector<bool> used(n, false);
            while (true) {
                a = base[a];
                used[a] = true;
                if (match[a] == -1) break;
                a = parent[match[a]];
            }
            while (true) {
                b = base[b];
                if (used[b]) return b;
                b = parent[match[b]];
            }
            return -1;
        };

        auto mark_path = [&](int v, int b, int children) {
            while (base[v] != b) {
                color[base[v]] = color[base[match[v]]] = 1;
                parent[v] = children;
                children = match[v];
                v = parent[match[v]];
            }
        };

        auto bfs = [&](int start) -> bool {
            std::fill(parent.begin(), parent.end(), -1);
            std::fill(color.begin(), color.end(), 0);
            for (int i = 0; i < n; i++) base[i] = i;

            std::queue<int> q;
            q.push(start);
            color[start] = 1;

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : adj[u]) {
                    if (base[u] == base[v] || color[v] == 2) continue;

                    if (color[v] == 0) {
                        color[v] = 2;
                        parent[v] = u;

                        if (match[v] == -1) {
                            while (v != -1) {
                                int pv = parent[v];
                                int ppv = match[pv];
                                match[v] = pv;
                                match[pv] = v;
                                v = ppv;
                            }
                            return true;
                        }

                        color[match[v]] = 1;
                        q.push(match[v]);
                    } else {
                        int b = lca(u, v);
                        mark_path(u, b, v);
                        mark_path(v, b, u);

                        for (int i = 0; i < n; i++) {
                            if (color[base[i]] == 1) {
                                base[i] = b;
                                if (color[i] == 1) {
                                    color[i] = 2;
                                    q.push(i);
                                }
                            }
                        }
                    }
                }
            }
            return false;
        };

        bool improved = true;
        while (improved) {
            improved = false;
            for (int i = 0; i < n; i++) {
                if (match[i] == -1 && bfs(i)) {
                    improved = true;
                }
            }
        }

        std::vector<std::pair<int, int>> result;
        for (int i = 0; i < n; i++) {
            if (match[i] != -1 && i < match[i]) {
                result.push_back({indexToId[i], indexToId[match[i]]});
            }
        }

        return result;

    } catch (const std::exception& e) {
        std::cerr << "Ошибка в алгоритме Эдмондса: " << e.what() << std::endl;
        throw;
    }
}

std::vector<std::pair<int, int>> Graph::findMaximumMatchingBipartite() {
    try {
        std::map<int, int> partition;
        if (!isBipartite(partition)) {
            throw std::invalid_argument("Граф не является двудольным");
        }

        if (vertices.empty()) {
            return {};
        }

        std::vector<int> left, right;
        for (const auto& vertex : vertices) {
            if (partition[vertex.getId()] == 0) {
                left.push_back(vertex.getId());
            } else {
                right.push_back(vertex.getId());
            }
        }

        std::map<int, int> idToIndex;
        std::vector<int> indexToId;
        for (const auto& vertex : vertices) {
            idToIndex[vertex.getId()] = indexToId.size();
            indexToId.push_back(vertex.getId());
        }

        int n = vertices.size();
        int leftSize = left.size();

        std::vector<std::vector<bool>> adj(n, std::vector<bool>(n, false));
        for (const auto& edge : edges) {
            int u = idToIndex[edge.getFromId()];
            int v = idToIndex[edge.getToId()];
            adj[u][v] = adj[v][u] = true;
        }

        std::vector<int> match(n, -1);

        for (int u = 0; u < leftSize; u++) {
            std::vector<bool> used(n, false);
            std::vector<int> parent(n, -1);
            std::queue<int> q;

            q.push(u);
            used[u] = true;
            bool found = false;
            int last = -1;

            while (!q.empty() && !found) {
                int current = q.front();
                q.pop();

                for (int v = leftSize; v < n; v++) {
                    if (adj[current][v] && !used[v]) {
                        used[v] = true;
                        parent[v] = current;

                        if (match[v] == -1) {
                            found = true;
                            last = v;
                            break;
                        } else {
                            q.push(match[v]);
                            parent[match[v]] = v;
                            used[match[v]] = true;
                        }
                    }
                }
            }

            if (found) {
                int v = last;
                while (v != -1) {
                    int p = parent[v];
                    int next = match[p];
                    match[v] = p;
                    match[p] = v;
                    v = next;
                }
            }
        }

        std::vector<std::pair<int, int>> result;
        for (int i = 0; i < n; i++) {
            if (match[i] != -1 && i < match[i]) {
                result.push_back({indexToId[i], indexToId[match[i]]});
            }
        }

        return result;

    } catch (const std::exception& e) {
        std::cerr << "Ошибка в алгоритме Куна: " << e.what() << std::endl;
        throw;
    }
}
