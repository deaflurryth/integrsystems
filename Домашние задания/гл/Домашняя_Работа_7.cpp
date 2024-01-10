#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

// Задание 1. Определение структуры для узла бинарного дерева
struct BinaryNode {
    int data;
    BinaryNode *leftChild;
    BinaryNode *rightChild;

    BinaryNode(int val) : data(val), leftChild(nullptr), rightChild(nullptr) {}
};

// Класс для представления двоичного дерева поиска
class BinarySearchTree {
public:
    BinaryNode *root;

    BinarySearchTree() : root(nullptr) {}

    // Функция для добавления нового узла в дерево
    void addNode(int val) {
        root = insertNode(root, val);
    }

    // Функция для проверки наличия значения в дереве
    bool hasValue(int val) {
        return searchNode(root, val);
    }

private:
    // Рекурсивная функция для добавления узла
    BinaryNode* insertNode(BinaryNode *node, int val) {
        if (node == nullptr) {
            return new BinaryNode(val);
        }

        if (val < node->data) {
            node->leftChild = insertNode(node->leftChild, val);
        } else if (val > node->data) {
            node->rightChild = insertNode(node->rightChild, val);
        }

        return node;
    }

    // Рекурсивная функция для поиска значения
    bool searchNode(BinaryNode *node, int val) {
        if (node == nullptr) {
            return false;
        }

        if (val == node->data) {
            return true;
        } else if (val < node->data) {
            return searchNode(node->leftChild, val);
        } else {
            return searchNode(node->rightChild, val);
        }
    }
};

// Задание 2. Определение класса для представления максимальной кучи
class MaxHeap {
public:
    std::vector<int> heapData;

    // Функция для добавления элемента в кучу
    void addValue(int val) {
        heapData.push_back(val); // Добавляем элемент в конец вектора
        std::push_heap(heapData.begin(), heapData.end()); // Переупорядочиваем элементы
    }

    // Функция для удаления наибольшего элемента (корня кучи)
    int removeTop() {
        if (heapData.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        std::pop_heap(heapData.begin(), heapData.end()); // Перемещает наибольший элемент в конец вектора
        int max = heapData.back(); // Получаем наибольший элемент
        heapData.pop_back(); // Удаляем элемент из вектора
        return max;
    }

    // Функция для проверки наличия элемента в куче
    bool includes(int val) {
        return std::find(heapData.begin(), heapData.end(), val) != heapData.end();
    }
};

// Задание 3. Определение структуры для узла односвязного списка
struct SingleLinkNode {
    int item;
    SingleLinkNode *next;

    SingleLinkNode(int val) : item(val), next(nullptr) {}
};

// Класс для представления односвязного списка
class LinkedList {
public:
    SingleLinkNode *head;

    LinkedList() : head(nullptr) {}

    // Функция для добавления элемента в конец списка
    void addToTail(int val) {
        if (head == nullptr) {
            head = new SingleLinkNode(val);
        } else {
            SingleLinkNode *current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new SingleLinkNode(val);
        }
    }

    // Функция для отображения всех элементов списка
    void displayList() {
        SingleLinkNode *current = head;
        while (current != nullptr) {
            std::cout << current->item << " -> ";
            current = current->next;
        }
        std::cout << "null" << std::endl;
    }
};

// Задание 4. Определение структуры для узла префиксного дерева
class PrefixTreeNode {
public:
    bool terminatesWord;
    std::unordered_map<char, PrefixTreeNode*> children;

    PrefixTreeNode() : terminatesWord(false) {}

    ~PrefixTreeNode() {
        for (auto &child : children) {
            delete child.second;
        }
    }
};

// Класс для представления префиксного дерева
class Trie {
public:
    PrefixTreeNode *root;

    Trie() : root(new PrefixTreeNode()) {}
    ~Trie() { delete root; }

    // Функция для добавления слова в префиксное дерево
    void addWord(const std::string &word) {
        PrefixTreeNode *node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new PrefixTreeNode();
            }
            node = node->children[c];
        }
        node->terminatesWord = true;
    }

    // Функция для проверки наличия слова в префиксном дереве
    bool containsWord(const std::string &word) {
        PrefixTreeNode *node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return node != nullptr && node->terminatesWord;
    }
};

int main() {
    // Работа с бинарным деревом поиска
    BinarySearchTree bst;
    bst.addNode(8);
    bst.addNode(3);
    bst.addNode(10);
    bst.addNode(1);
    bst.addNode(6);
    bst.addNode(14);
    bst.addNode(4);
    bst.addNode(7);
    bst.addNode(13);
    std::cout << "Наличие числа 10 в дереве: " << bst.hasValue(10) << std::endl;
    std::cout << "Наличие числа 5 в дереве: " << bst.hasValue(5) << std::endl;

    // Работа с максимальной кучей
    MaxHeap heap;
    heap.addValue(3);
    heap.addValue(1);
    heap.addValue(6);
    heap.addValue(5);
    heap.addValue(2);
    heap.addValue(4);
    std::cout << "Наличие числа 6 в куче: " << heap.includes(6) << std::endl;
    std::cout << "Наличие числа 10 в куче: " << heap.includes(10) << std::endl;
    std::cout << "Максимальный элемент в куче: " << heap.removeTop() << std::endl;

    // Работа с односвязным списком
    LinkedList list;
    list.addToTail(1);
    list.addToTail(2);
    list.addToTail(3);
    list.addToTail(4);
    list.addToTail(5);
    list.displayList();

    // Работа с префиксным деревом
    Trie trie;
    trie.addWord("java");
    trie.addWord("script");
    trie.addWord("stripe");
    trie.addWord("python");
    trie.addWord("c++");
    trie.addWord("ruby");
    std::cout << "Наличие слова 'java' в префиксном дереве: " << trie.containsWord("java") << std::endl;
    std::cout << "Наличие слова 'script' в префиксном дереве: " << trie.containsWord("script") << std::endl;
    std::cout << "Наличие слова 'forever' в префиксном дереве: " << trie.containsWord("forever") << std::endl;

    return 0;
}
