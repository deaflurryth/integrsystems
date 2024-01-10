#include <iostream>
#include <vector>
#include <utility>
#include <optional>

class DescendingPriorityQueue {
public:
    void addWithPriority(int value, int priority) {
        auto position = findInsertPosition(priority);
        elements.insert(position, std::make_pair(value, priority));
    }

    std::optional<std::pair<int, int> > removeHighestPriority() {
        if (!elements.empty()) {
            auto highestPriorityElement = elements.front();
            elements.erase(elements.begin());
            return highestPriorityElement;
        }
        return {}; // Возвращаем пустой optional, если очередь пуста
    }

    bool isEmpty() const {
        return elements.empty();
    }

private:
    std::vector<std::pair<int, int> > elements; // Вектор пар (значение, приоритет)

    auto findInsertPosition(int priority) {
        return std::find_if(elements.begin(), elements.end(),
                            [priority](const auto& el) { return el.second < priority; });
    }
};

template <typename T>
class ArrayCircularQueue {
public:
    ArrayCircularQueue(int capacity) : capacity(capacity), head(-1), tail(-1) {
        queue = new T[capacity];
    }

    ~ArrayCircularQueue() {
        delete[] queue;
    }

    bool isFull() const {
        return (head == 0 && tail == capacity - 1) || (tail == (head - 1) % (capacity - 1));
    }

    bool isEmpty() const {
        return head == -1;
    }

    void add(T element) {
        if (isFull()) {
            throw std::runtime_error("Queue is full");
        }

        if (isEmpty()) {
            head = tail = 0;
        } else if (tail == capacity - 1 && head != 0) {
            tail = 0;
        } else {
            tail++;
        }

        queue[tail] = element;
    }

    std::optional<T> remove() {
        if (isEmpty()) {
            return {};
        }

        T element = queue[head];
        queue[head] = T(); // Очистка элемента

        if (head == tail) {
            head = tail = -1;
        } else if (head == capacity - 1) {
            head = 0;
        } else {
            head++;
        }

        return element;
    }

    std::optional<T> getFront() const {
        if (isEmpty()) {
            return {};
        }
        return queue[head];
    }

private:
    int head, tail, capacity;
    T* queue;
};

int main() {
    DescendingPriorityQueue priorityQueue;

    priorityQueue.addWithPriority(10, 2);
    priorityQueue.addWithPriority(5, 1);
    priorityQueue.addWithPriority(20, 3);

    while (!priorityQueue.isEmpty()) {
        auto element = priorityQueue.removeHighestPriority();
        if (element) {
            std::cout << "Value: " << element->first << ", Priority: " << element->second << std::endl;
        }
    }

    std::cout << "------" << std::endl;

    ArrayCircularQueue<int> circularQueue(5);

    try {
        circularQueue.add(1);
        circularQueue.add(2);
        circularQueue.add(3);
        circularQueue.add(4);
        circularQueue.add(5);
        circularQueue.add(6); // Вызовет исключение
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    auto frontElement = circularQueue.getFront();
    if (frontElement) {
        std::cout << "Первый элемент: " << *frontElement << std::endl;
    }

    auto removedElement = circularQueue.remove();
    if (removedElement) {
        std::cout << "Удаленный элемент: " << *removedElement << std::endl;
    }

    // Повторяем для второго элемента
    removedElement = circularQueue.remove();
    if (removedElement) {
        std::cout << "Удаленный элемент: " << *removedElement << std::endl;
    }

    circularQueue.add(6);
    frontElement = circularQueue.getFront();
    if (frontElement) {
        std::cout << "Первый элемент после добавления элементов: " << *frontElement << std::endl;
    }

    return 0;
}
