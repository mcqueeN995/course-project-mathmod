#include "graph.h"
#include <fstream>
#include <iostream>

int main() {
    try {
        std::cout << "=== ПРОВЕРКА ГРАФА НА ДВУДОЛЬНОСТЬ ===" << std::endl;
        std::cout << "\n--- ПРИМЕР 1: Двудольный граф ---" << std::endl;

        try {
            Graph bipartiteGraph;
            bipartiteGraph.addVertex(Vertex(1, "A", 10.0));
            bipartiteGraph.addVertex(Vertex(2, "B", 20.0));
            bipartiteGraph.addVertex(Vertex(3, "C", 15.0));
            bipartiteGraph.addVertex(Vertex(4, "D", 25.0));

            bipartiteGraph.addEdge(Edge(1, 2, 5.0, false));  // 1 -- 2
            bipartiteGraph.addEdge(Edge(1, 4, 3.0, false));  // 1 -- 4
            bipartiteGraph.addEdge(Edge(3, 2, 7.0, false));  // 3 -- 2
            bipartiteGraph.addEdge(Edge(3, 4, 2.0, false));  // 3 -- 4

            std::cout << "\nГраф 1:" << std::endl;
            bipartiteGraph.printGraph();

            std::map<int, int> partition1;
            bool isBipartite1 = bipartiteGraph.isBipartite(partition1);

            std::cout << "Результат: Граф " << (isBipartite1 ? "ДВУДОЛЬНЫЙ" : "НЕ ДВУДОЛЬНЫЙ") << std::endl;

            if (isBipartite1) {
                bipartiteGraph.printBipartiteInfo(partition1);
            }
        } catch (const std::exception& e) {
            std::cerr << "Ошибка в примере 1: " << e.what() << std::endl;
        }

        std::cout << "\n--- ПРИМЕР 2: Не двудольный граф (нечётный цикл) ---" << std::endl;

        try {
            Graph nonBipartiteGraph;

            nonBipartiteGraph.addVertex(Vertex(1, "X", 10.0));
            nonBipartiteGraph.addVertex(Vertex(2, "Y", 20.0));
            nonBipartiteGraph.addVertex(Vertex(3, "Z", 15.0));

            nonBipartiteGraph.addEdge(Edge(1, 2, 5.0, false));  // 1 -- 2
            nonBipartiteGraph.addEdge(Edge(2, 3, 3.0, false));  // 2 -- 3
            nonBipartiteGraph.addEdge(Edge(3, 1, 4.0, false));  // 3 -- 1

            std::cout << "\nГраф 2:" << std::endl;
            nonBipartiteGraph.printGraph();

            std::map<int, int> partition2;
            bool isBipartite2 = nonBipartiteGraph.isBipartite(partition2);

            std::cout << "Результат: Граф " << (isBipartite2 ? "ДВУДОЛЬНЫЙ" : "НЕ ДВУДОЛЬНЫЙ") << std::endl;

            if (isBipartite2) {
                nonBipartiteGraph.printBipartiteInfo(partition2);
            }

        } catch (const std::exception& e) {
            std::cerr << "Ошибка в примере 2: " << e.what() << std::endl;
        }

        std::cout << "\n--- ПРИМЕР 3: Граф с несколькими компонентами ---" << std::endl;

        try {
            Graph multiComponentGraph;

            multiComponentGraph.addVertex(Vertex(1, "P", 10.0));
            multiComponentGraph.addVertex(Vertex(2, "Q", 20.0));
            multiComponentGraph.addEdge(Edge(1, 2, 5.0, false));

            multiComponentGraph.addVertex(Vertex(3, "R", 15.0));
            multiComponentGraph.addVertex(Vertex(4, "S", 25.0));
            multiComponentGraph.addVertex(Vertex(5, "T", 30.0));
            multiComponentGraph.addEdge(Edge(3, 4, 3.0, false));
            multiComponentGraph.addEdge(Edge(4, 5, 2.0, false));

            std::cout << "\nГраф 3:" << std::endl;
            multiComponentGraph.printGraph();

            std::map<int, int> partition3;
            bool isBipartite3 = multiComponentGraph.isBipartite(partition3);

            std::cout << "Результат: Граф " << (isBipartite3 ? "ДВУДОЛЬНЫЙ" : "НЕ ДВУДОЛЬНЫЙ") << std::endl;

            if (isBipartite3) {
                multiComponentGraph.printBipartiteInfo(partition3);
            }

        } catch (const std::exception& e) {
            std::cerr << "Ошибка в примере 3: " << e.what() << std::endl;
        }

        std::cout << "\n--- ПРИМЕР 4: Загрузка графа из файла и проверка ---" << std::endl;

        try {
            Graph saveGraph;
            saveGraph.addVertex(Vertex(1, "V1", 1.0));
            saveGraph.addVertex(Vertex(2, "V2", 2.0));
            saveGraph.addVertex(Vertex(3, "V3", 3.0));
            saveGraph.addVertex(Vertex(4, "V4", 4.0));

            saveGraph.addEdge(Edge(1, 2, 1.0, false));
            saveGraph.addEdge(Edge(2, 3, 1.0, false));
            saveGraph.addEdge(Edge(3, 4, 1.0, false));

            std::ofstream outFile("bipartite_test.txt");
            if (!outFile.is_open()) {
                throw std::ios_base::failure("Не удалось открыть файл для записи");
            }
            outFile << saveGraph;
            outFile.close();

            std::cout << "Граф сохранён в файл 'bipartite_test.txt'" << std::endl;

            std::ifstream inFile("bipartite_test.txt");
            if (!inFile.is_open()) {
                throw std::ios_base::failure("Не удалось открыть файл для чтения");
            }

            Graph loadedGraph;
            inFile >> loadedGraph;
            inFile.close();

            std::cout << "\nЗагруженный граф:" << std::endl;
            loadedGraph.printGraph();

            std::map<int, int> partition4;
            bool isBipartite4 = loadedGraph.isBipartite(partition4);

            std::cout << "Результат: Граф " << (isBipartite4 ? "ДВУДОЛЬНЫЙ" : "НЕ ДВУДОЛЬНЫЙ") << std::endl;

            if (isBipartite4) {
                loadedGraph.printBipartiteInfo(partition4);
            }

        } catch (const std::exception& e) {
            std::cerr << "Ошибка в примере 4: " << e.what() << std::endl;
        }

        std::cout << "\n=== ПРОГРАММА ЗАВЕРШЕНА ===" << std::endl;

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "КРИТИЧЕСКАЯ ОШИБКА: " << e.what() << std::endl;
        return 1;
    }
}
