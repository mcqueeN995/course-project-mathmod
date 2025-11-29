#include "graph.h"
#include <fstream>
#include <iostream>

int main() {
    try {
        std::cout << "=== СОЗДАНИЕ ГРАФА ===" << std::endl;

        Graph graph;

        std::cout << "\nДобавляем вершины..." << std::endl;

        try {
            graph.addVertex(Vertex(1, "NodeA", 10.0));
            graph.addVertex(Vertex(2, "NodeB", 20.0));
            graph.addVertex(Vertex(3, "NodeC", 15.0));
            graph.addVertex(Vertex(4, "NodeD", 25.0));

            std::cout << "✓ Вершины добавлены успешно" << std::endl;

        } catch (const std::exception& e) {
            std::cerr << "Ошибка при добавлении вершин: " << e.what() << std::endl;
            return 1;
        }

        std::cout << "\nДобавляем рёбра..." << std::endl;

        try {
            graph.addEdge(Edge(1, 2, 5.0, true));   // Направленное ребро 1->2
            graph.addEdge(Edge(2, 3, 3.5, false));  // Ненаправленное ребро 2--3
            graph.addEdge(Edge(3, 4, 7.2, true));   // Направленное ребро 3->4
            graph.addEdge(Edge(1, 4, 10.0, false)); // Ненаправленное ребро 1--4

            std::cout << "✓ Рёбра добавлены успешно" << std::endl;

        } catch (const std::exception& e) {
            std::cerr << "Ошибка при добавлении рёбер: " << e.what() << std::endl;
            return 1;
        }

        std::cout << std::endl;
        graph.printGraph();

        std::cout << "Сохраняем граф в файл 'graph.txt'..." << std::endl;

        try {
            std::ofstream outFile("graph.txt");

            if (!outFile.is_open()) {
                throw std::ios_base::failure("Не удалось открыть файл для записи");
            }

            outFile << graph;

            if (!outFile) {
                throw std::ios_base::failure("Ошибка при записи в файл");
            }

            outFile.close();
            std::cout << "✓ Граф успешно сохранён в файл" << std::endl;

        } catch (const std::ios_base::failure& e) {
            std::cerr << "Ошибка ввода/вывода при сохранении: " << e.what() << std::endl;
            return 1;
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при сохранении графа: " << e.what() << std::endl;
            return 1;
        }

        std::cout << "\nЗагружаем граф из файла 'graph.txt'..." << std::endl;

        try {
            std::ifstream inFile("graph.txt");
            if (!inFile.is_open()) {
                throw std::ios_base::failure("Не удалось открыть файл для чтения");
            }

            Graph loadedGraph;

            inFile >> loadedGraph;

            if (!inFile) {
                throw std::ios_base::failure("Ошибка при чтении из файла");
            }

            inFile.close();
            std::cout << "✓ Граф успешно загружен из файла" << std::endl;

            std::cout << std::endl;
            loadedGraph.printGraph();

        } catch (const std::ios_base::failure& e) {
            std::cerr << "Ошибка ввода/вывода при загрузке: " << e.what() << std::endl;
            return 1;
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при загрузке графа: " << e.what() << std::endl;
            return 1;
        }

        std::cout << "\n=== ДОБАВЛЕНИЕ НОВОЙ ВЕРШИНЫ ИЗ КОНСОЛИ ===" << std::endl;

        try {
            std::cout << "Введите данные вершины (ID Label Weight): ";
            Vertex newVertex;
            std::cin >> newVertex;
            try {
                graph.addVertex(newVertex);
                std::cout << "✓ Новая вершина добавлена в оригинальный граф" << std::endl;
            } catch (const std::invalid_argument& e) {
                std::cerr << "Вершина не добавлена: " << e.what() << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при вводе вершины: " << e.what() << std::endl;
        }

        std::cout << std::endl;
        graph.printGraph();

        std::cout << "=== ПРОГРАММА ЗАВЕРШЕНА УСПЕШНО ===" << std::endl;

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "КРИТИЧЕСКАЯ ОШИБКА: " << e.what() << std::endl;
        return 1;
    }
}
