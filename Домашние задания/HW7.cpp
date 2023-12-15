//
// Created by deaflurryth ¿ on 13.12.2023.
//

#include <iostream>
#include <vector>
#include <utility>

// очередь с нисходящим приоритетом
class Priority_Queue {
public:
    void insert(int value, int priority) {
        // Находим правильное место для вставки элемента с учетом его приоритета
        bool inserted = false;
        for (auto it = elements.begin(); it != elements.end(); ++it) {
            // Если приоритет текущего элемента меньше, вставляем перед ним
            if (it->second < priority) {
                elements.insert(it, std::make_pair(value, priority));
                inserted = true;
                break;
            }
        }
        // Если элемент не был вставлен, значит его приоритет самый низкий, добавляем в конец
        if (!inserted) {
            elements.push_back(std::make_pair(value, priority));
        }
    }

    std::pair<int, int> extract() {
        // Удаляем элемент с наивысшим приоритетом (который находится в начале вектора)
        if (!elements.empty()) {
            auto element = elements.front();
            elements.erase(elements.begin());
            return element;
        }
        return std::make_pair(-1, -1); // Возвращаем пару невалидных значений, если очередь пуста
    }

    bool is_empty() const {
        return elements.empty();
    }

private:
    std::vector<std::pair<int, int> > elements; // Вектор пар (значение, приоритет)
};

//ADT с круговой очередью, используя Arrays
template <typename T>
class CircularQueue {
private:
    int front, rear, size;
    T *queue;

public:
    CircularQueue(int size) : size(size), front(-1), rear(-1) {
        queue = new T[size];
    }

    ~CircularQueue() {
        delete[] queue;
    }

    bool isFull() {
        return (front == 0 && rear == size - 1) || (rear == (front - 1) % (size - 1));
    }

    bool isEmpty() {
        return front == -1;
    }

    void enqueue(T element) {
        if (isFull()) {
            std::cout << "Очередь полна\n";
            return;
        }

        if (front == -1) { // Если очередь пуста
            front = rear = 0;
        } else if (rear == size - 1 && front != 0) { // Циклическое инкрементирование
            rear = 0;
        } else {
            rear++;
        }

        queue[rear] = element;
    }

    T dequeue() {
        if (isEmpty()) {
            std::cout << "Очередь пуста\n";
            return T(); // Возвращаем значение по умолчанию для типа T
        }

        T data = queue[front];
        queue[front] = T(); // Удалить элемент

        if (front == rear) { // Если элемент был последним в очереди
            front = rear = -1;
        } else if (front == size - 1) { // Циклическое инкрементирование
            front = 0;
        } else {
            front++;
        }

        return data;
    }

    T getFront() {
        if (isEmpty()) {
            std::cout << "Очередь пуста\n";
            return T(); // Возвращаем значение по умолчанию для типа T
        }
        return queue[front];
    }
};
int main() {
    //очередь с нисходящим приоритетом
    Priority_Queue pq;

    pq.insert(10, 2); // Вставляем элементы с разными приоритетами
    pq.insert(5, 1);
    pq.insert(20, 3);

    while (!pq.is_empty()) {
        auto element = pq.extract(); // Извлекаем элементы начиная с наивысшего приоритета
        std::cout << "Value: " << element.first << ", Priority: " << element.second << std::endl;
    }

    std::cout << "------" << std::endl;
    CircularQueue<int> q(5);

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    //ADT с круговой очередью, используя Arrays
    // должно быть сообщение о том, что очередь полна
    q.enqueue(6);

    std::cout << "Первый элемент: " << q.getFront() << std::endl; // 1

    std::cout << "Удаленный элемент: " << q.dequeue() << std::endl; // 1
    std::cout << "Удаленный элемент: " << q.dequeue() << std::endl; // 2

    q.enqueue(6);
    std::cout << "Первый элемент после добавления элементов: " << q.getFront() << std::endl; // должно быть 3
    return 0;
}
