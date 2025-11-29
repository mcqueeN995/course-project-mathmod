#include "graph.h"
#include <fstream>
#include <iostream>

int main() {
    try {
        std::cout << "=== ДЕМОНСТРАЦИЯ АЛГОРИТМОВ ПРОВЕРКИ ДВУДОЛЬНОСТИ ===" << std::endl;
        std::cout << "\n╔════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║ ДЕМОНСТРАЦИЯ 1: BFS - Двудольный граф              ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════╝" << std::endl;

        try {
            Graph graph1;

            graph1.addVertex(Vertex(1, "A", 10.0));
            graph1.addVertex(Vertex(2, "B", 20.0));
            graph1.addVertex(Vertex(3, "C", 15.0));
            graph1.addVertex(Vertex(4, "D", 25.0));

            graph1.addEdge(Edge(1, 2, 5.0, false));
            graph1.addEdge(Edge(1, 4, 3.0, false));
            graph1.addEdge(Edge(3, 2, 7.0, false));
            graph1.addEdge(Edge(3, 4, 2.0, false));

            std::cout << "\nГраф:" << std::endl;
            graph1.printGraph();

            std::cout << "Алгоритм: BFS (поиск в ширину)" << std::endl;
            std::map<int, int> partitionBFS1;
            bool isBipartiteBFS1 = graph1.isBipartite(partitionBFS1);
            std::cout << "Результат: " << (isBipartiteBFS1 ? "ДВУДОЛЬНЫЙ ✓" : "НЕ ДВУДОЛЬНЫЙ ✗") << std::endl;
            if (isBipartiteBFS1) {
                graph1.printBipartiteInfo(partitionBFS1);
            }

        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }

        std::cout << "\n╔════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║ ДЕМОНСТРАЦИЯ 2: BFS - Не двудольный граф           ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════╝" << std::endl;

        try {
            Graph graph2;

            graph2.addVertex(Vertex(1, "X", 10.0));
            graph2.addVertex(Vertex(2, "Y", 20.0));
            graph2.addVertex(Vertex(3, "Z", 15.0));

            graph2.addEdge(Edge(1, 2, 5.0, false));
            graph2.addEdge(Edge(2, 3, 3.0, false));
            graph2.addEdge(Edge(3, 1, 4.0, false));

            std::cout << "\nГраф (треугольник 1-2-3-1):" << std::endl;
            graph2.printGraph();

            std::cout << "Алгоритм: BFS (поиск в ширину)" << std::endl;
            std::map<int, int> partitionBFS2;
            bool isBipartiteBFS2 = graph2.isBipartite(partitionBFS2);
            std::cout << "Результат: " << (isBipartiteBFS2 ? "ДВУДОЛЬНЫЙ ✓" : "НЕ ДВУДОЛЬНЫЙ ✗") << std::endl;

        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }

        std::cout << "\n╔════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║ ДЕМОНСТРАЦИЯ 3: BFS - Несколько компонент          ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════╝" << std::endl;

        try {
            Graph graph3;

            graph3.addVertex(Vertex(1, "P", 10.0));
            graph3.addVertex(Vertex(2, "Q", 20.0));
            graph3.addVertex(Vertex(3, "R", 15.0));
            graph3.addVertex(Vertex(4, "S", 25.0));
            graph3.addVertex(Vertex(5, "T", 30.0));

            graph3.addEdge(Edge(1, 2, 5.0, false));
            graph3.addEdge(Edge(3, 4, 3.0, false));
            graph3.addEdge(Edge(4, 5, 2.0, false));

            std::cout << "\nГраф (две отдельные компоненты):" << std::endl;
            graph3.printGraph();

            std::cout << "Алгоритм: BFS (поиск в ширину)" << std::endl;
            std::map<int, int> partitionBFS3;
            bool isBipartiteBFS3 = graph3.isBipartite(partitionBFS3);
            std::cout << "Результат: " << (isBipartiteBFS3 ? "ДВУДОЛЬНЫЙ ✓" : "НЕ ДВУДОЛЬНЫЙ ✗") << std::endl;
            if (isBipartiteBFS3) {
                graph3.printBipartiteInfo(partitionBFS3);
            }

        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }

        std::cout << "\n╔════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║ ДЕМОНСТРАЦИЯ 4: DFS - Двудольный граф              ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════╝" << std::endl;

        try {
            Graph graph4;

            graph4.addVertex(Vertex(1, "A", 10.0));
            graph4.addVertex(Vertex(2, "B", 20.0));
            graph4.addVertex(Vertex(3, "C", 15.0));
            graph4.addVertex(Vertex(4, "D", 25.0));

            graph4.addEdge(Edge(1, 2, 5.0, false));
            graph4.addEdge(Edge(1, 4, 3.0, false));
            graph4.addEdge(Edge(3, 2, 7.0, false));
            graph4.addEdge(Edge(3, 4, 2.0, false));

            std::cout << "\nГраф:" << std::endl;
            graph4.printGraph();

            std::cout << "Алгоритм: DFS (поиск в глубину)" << std::endl;
            std::map<int, int> partitionDFS1;
            bool isBipartiteDFS1 = graph4.isBipartiteDFS(partitionDFS1);
            std::cout << "Результат: " << (isBipartiteDFS1 ? "ДВУДОЛЬНЫЙ ✓" : "НЕ ДВУДОЛЬНЫЙ ✗") << std::endl;
            if (isBipartiteDFS1) {
                graph4.printBipartiteInfo(partitionDFS1);
            }

        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }

        std::cout << "\n╔════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║ ДЕМОНСТРАЦИЯ 5: DFS - Не двудольный граф           ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════╝" << std::endl;

        try {
            Graph graph5;

            graph5.addVertex(Vertex(1, "X", 10.0));
            graph5.addVertex(Vertex(2, "Y", 20.0));
            graph5.addVertex(Vertex(3, "Z", 15.0));

            graph5.addEdge(Edge(1, 2, 5.0, false));
            graph5.addEdge(Edge(2, 3, 3.0, false));
            graph5.addEdge(Edge(3, 1, 4.0, false));

            std::cout << "\nГраф (треугольник 1-2-3-1):" << std::endl;
            graph5.printGraph();

            std::cout << "Алгоритм: DFS (поиск в глубину)" << std::endl;
            std::map<int, int> partitionDFS2;
            bool isBipartiteDFS2 = graph5.isBipartiteDFS(partitionDFS2);
            std::cout << "Результат: " << (isBipartiteDFS2 ? "ДВУДОЛЬНЫЙ ✓" : "НЕ ДВУДОЛЬНЫЙ ✗") << std::endl;

        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }

        std::cout << "\n╔════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║ ДЕМОНСТРАЦИЯ 6: DFS - Несколько компонент          ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════╝" << std::endl;

        try {
            Graph graph6;

            graph6.addVertex(Vertex(1, "P", 10.0));
            graph6.addVertex(Vertex(2, "Q", 20.0));
            graph6.addVertex(Vertex(3, "R", 15.0));
            graph6.addVertex(Vertex(4, "S", 25.0));
            graph6.addVertex(Vertex(5, "T", 30.0));

            graph6.addEdge(Edge(1, 2, 5.0, false));
            graph6.addEdge(Edge(3, 4, 3.0, false));
            graph6.addEdge(Edge(4, 5, 2.0, false));

            std::cout << "\nГраф (две отдельные компоненты):" << std::endl;
            graph6.printGraph();

            std::cout << "Алгоритм: DFS (поиск в глубину)" << std::endl;
            std::map<int, int> partitionDFS3;
            bool isBipartiteDFS3 = graph6.isBipartiteDFS(partitionDFS3);
            std::cout << "Результат: " << (isBipartiteDFS3 ? "ДВУДОЛЬНЫЙ ✓" : "НЕ ДВУДОЛЬНЫЙ ✗") << std::endl;
            if (isBipartiteDFS3) {
                graph6.printBipartiteInfo(partitionDFS3);
            }

        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }

        std::cout << "\n╔════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║ ДЕМОНСТРАЦИЯ 7: Загрузка из файла + BFS            ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════╝" << std::endl;

        try {
            Graph saveGraph;
            saveGraph.addVertex(Vertex(1, "V1", 1.0));
            saveGraph.addVertex(Vertex(2, "V2", 2.0));
            saveGraph.addVertex(Vertex(3, "V3", 3.0));
            saveGraph.addVertex(Vertex(4, "V4", 4.0));

            saveGraph.addEdge(Edge(1, 2, 1.0, false));
            saveGraph.addEdge(Edge(2, 3, 1.0, false));
            saveGraph.addEdge(Edge(3, 4, 1.0, false));

            std::ofstream outFile("bipartite_bfs_test.txt");
            if (!outFile.is_open()) {
                throw std::ios_base::failure("Не удалось открыть файл для записи");
            }
            outFile << saveGraph;
            outFile.close();

            std::cout << "\nГраф сохранён в файл 'bipartite_bfs_test.txt'" << std::endl;

            std::ifstream inFile("bipartite_bfs_test.txt");
            if (!inFile.is_open()) {
                throw std::ios_base::failure("Не удалось открыть файл для чтения");
            }

            Graph loadedGraph;
            inFile >> loadedGraph;
            inFile.close();

            std::cout << "\nЗагруженный граф:" << std::endl;
            loadedGraph.printGraph();

            std::cout << "Алгоритм: BFS (поиск в ширину)" << std::endl;
            std::map<int, int> partitionBFS;
            bool isBipartiteBFS = loadedGraph.isBipartite(partitionBFS);
            std::cout << "Результат: " << (isBipartiteBFS ? "ДВУДОЛЬНЫЙ ✓" : "НЕ ДВУДОЛЬНЫЙ ✗") << std::endl;
            if (isBipartiteBFS) {
                loadedGraph.printBipartiteInfo(partitionBFS);
            }

        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }

        std::cout << "\n╔════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║ ДЕМОНСТРАЦИЯ 8: Загрузка из файла + DFS            ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════╝" << std::endl;

        try {
            Graph saveGraph2;
            saveGraph2.addVertex(Vertex(1, "V1", 1.0));
            saveGraph2.addVertex(Vertex(2, "V2", 2.0));
            saveGraph2.addVertex(Vertex(3, "V3", 3.0));
            saveGraph2.addVertex(Vertex(4, "V4", 4.0));

            saveGraph2.addEdge(Edge(1, 2, 1.0, false));
            saveGraph2.addEdge(Edge(2, 3, 1.0, false));
            saveGraph2.addEdge(Edge(3, 4, 1.0, false));

            std::ofstream outFile2("bipartite_dfs_test.txt");
            if (!outFile2.is_open()) {
                throw std::ios_base::failure("Не удалось открыть файл для записи");
            }
            outFile2 << saveGraph2;
            outFile2.close();

            std::cout << "\nГраф сохранён в файл 'bipartite_dfs_test.txt'" << std::endl;

            std::ifstream inFile2("bipartite_dfs_test.txt");
            if (!inFile2.is_open()) {
                throw std::ios_base::failure("Не удалось открыть файл для чтения");
            }

            Graph loadedGraph2;
            inFile2 >> loadedGraph2;
            inFile2.close();

            std::cout << "\nЗагруженный граф:" << std::endl;
            loadedGraph2.printGraph();

            std::cout << "Алгоритм: DFS (поиск в глубину)" << std::endl;
            std::map<int, int> partitionDFS;
            bool isBipartiteDFS = loadedGraph2.isBipartiteDFS(partitionDFS);
            std::cout << "Результат: " << (isBipartiteDFS ? "ДВУДОЛЬНЫЙ ✓" : "НЕ ДВУДОЛЬНЫЙ ✗") << std::endl;
            if (isBipartiteDFS) {
                loadedGraph2.printBipartiteInfo(partitionDFS);
            }

        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }

        std::cout << "\n╔════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║ ПРОГРАММА ЗАВЕРШЕНА                                ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════╝" << std::endl;

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "КРИТИЧЕСКАЯ ОШИБКА: " << e.what() << std::endl;
        return 1;
    }
}
