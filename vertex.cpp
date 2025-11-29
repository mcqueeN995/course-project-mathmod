#include "vertex.h"
#include <stdexcept>

// Конструктор по умолчанию
// Инициализирует вершину с нулевыми значениями
Vertex::Vertex() : id(0), label(""), weight(0.0) {}

// Параметризованный конструктор
// Принимает все параметры вершины и проверяет их валидность
Vertex::Vertex(int id, const std::string& label, double weight)
    : id(id), label(label), weight(weight) {

    // Проверка на отрицательный ID - ID должен быть неотрицательным
    if (id < 0) {
        throw std::invalid_argument("ID вершины не может быть отрицательным");
    }

    // Проверка на пустую метку - каждая вершина должна иметь описание
    if (label.empty()) {
        throw std::invalid_argument("Метка вершины не может быть пустой");
    }
}

// Геттер для ID
int Vertex::getId() const {
    return id;
}

// Геттер для метки
std::string Vertex::getLabel() const {
    return label;
}

// Геттер для веса
double Vertex::getWeight() const {
    return weight;
}

// Сеттер для ID с валидацией
void Vertex::setId(int newId) {
    if (newId < 0) {
        throw std::invalid_argument("ID вершины не может быть отрицательным");
    }
    id = newId;
}

// Сеттер для метки с валидацией
void Vertex::setLabel(const std::string& newLabel) {
    if (newLabel.empty()) {
        throw std::invalid_argument("Метка вершины не может быть пустой");
    }
    label = newLabel;
}

// Сеттер для веса
void Vertex::setWeight(double newWeight) {
    weight = newWeight;
}

// Оператор вывода <<
// Позволяет выводить информацию о вершине в поток (консоль или файл)
// Формат: "ID: 1 | Label: NodeA | Weight: 5.5"
std::ostream& operator<<(std::ostream& os, const Vertex& vertex) {
    try {
        // Выводим все параметры вершины в формате "ключ: значение"
        os << "ID: " << vertex.id
           << " | Label: " << vertex.label
           << " | Weight: " << vertex.weight;

        // Проверяем, был ли успешен вывод
        if (!os) {
            throw std::ios_base::failure("Ошибка при выводе вершины в поток");
        }

        return os;
    } catch (const std::ios_base::failure& e) {
        // Обрабатываем ошибки потока
        std::cerr << "Ошибка ввода/вывода: " << e.what() << std::endl;
        throw;
    }
}

// Оператор ввода >>
// Позволяет читать информацию о вершине из потока (консоль или файл)
// Ожидает формат: "1 NodeA 5.5"
std::istream& operator>>(std::istream& is, Vertex& vertex) {
    try {
        int tempId;
        std::string tempLabel;
        double tempWeight;

        // Пытаемся прочитать ID
        if (!(is >> tempId)) {
            throw std::invalid_argument("Не удалось прочитать ID вершины");
        }

        // Пытаемся прочитать метку (одно слово без пробелов)
        if (!(is >> tempLabel)) {
            throw std::invalid_argument("Не удалось прочитать метку вершины");
        }

        // Пытаемся прочитать вес
        if (!(is >> tempWeight)) {
            throw std::invalid_argument("Не удалось прочитать вес вершины");
        }

        // Проверяем корректность прочитанных данных
        if (tempId < 0) {
            throw std::invalid_argument("ID вершины не может быть отрицательным");
        }

        if (tempLabel.empty()) {
            throw std::invalid_argument("Метка вершины не может быть пустой");
        }

        // Если всё корректно, присваиваем значения
        vertex.id = tempId;
        vertex.label = tempLabel;
        vertex.weight = tempWeight;

        return is;

    } catch (const std::invalid_argument& e) {
        // Обрабатываем ошибки валидации данных
        std::cerr << "Ошибка при вводе вершины: " << e.what() << std::endl;
        is.setstate(std::ios_base::failbit);  // Устанавливаем флаг ошибки потока
        throw;
    } catch (const std::exception& e) {
        // Обрабатываем прочие исключения
        std::cerr << "Неожиданная ошибка при вводе вершины: " << e.what() << std::endl;
        is.setstate(std::ios_base::failbit);
        throw;
    }
}
