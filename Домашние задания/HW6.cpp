//
// Created by deaflurryth ¿ on 07.12.2023.
//
#include <iostream>
#include <vector>
#include <algorithm>

// Задание 1. Определение структуры для узла дерева
struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : value(x), left(nullptr), right(nullptr) {}
};

// Класс для представления двоичного дерева поиска
class BinarySearchTree {
public:
    TreeNode *root;

    BinarySearchTree() : root(nullptr) {}

    // Функция для вставки нового значения в дерево
    void insert(int value) {
        root = insertIntoBST(root, value);
    }

    // Функция для поиска значения в дереве
    bool contains(int value) {
        return searchBST(root, value);
    }

private:
    // Рекурсивная функция для вставки
    TreeNode* insertIntoBST(TreeNode *node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }

        if (value < node->value) {
            node->left = insertIntoBST(node->left, value);
        } else if (value > node->value) {
            node->right = insertIntoBST(node->right, value);
        }

        return node;
    }

    // Рекурсивная функция для поиска
    bool searchBST(TreeNode *node, int value) {
        if (node == nullptr) {
            return false;
        }

        if (value == node->value) {
            return true;
        } else if (value < node->value) {
            return searchBST(node->left, value);
        } else {
            return searchBST(node->right, value);
        }
    }
};


//ЗАДАНИЕ 2
class MaxHeap {
public:
    std::vector<int> heap;

    // Функция для добавления элемента в кучу
    void insert(int value) {
        heap.push_back(value); // Добавляем элемент в конец вектора
        std::push_heap(heap.begin(), heap.end()); // Переупорядочиваем элементы
    }

    // Функция для удаления максимального элемента (корня кучи)
    int extractMax() {
        if (heap.size() == 0) {
            throw std::out_of_range("Heap is empty");
        }
        std::pop_heap(heap.begin(), heap.end()); // Перемещает максимальный элемент в конец вектора
        int max = heap.back(); // Получаем максимальный элемент
        heap.pop_back(); // Удаляем элемент из вектора
        return max;
    }

    // Функция для поиска значения в куче
    bool contains(int value) {
        return std::find(heap.begin(), heap.end(), value) != heap.end();
    }
};


//ЗАДАНИЕ 3
struct ListNode {
    int value;
    ListNode *next;

    ListNode(int x) : value(x), next(nullptr) {}
};

// Класс для представления односвязного списка
class LinkedList {
public:
    ListNode *head;

    LinkedList() : head(nullptr) {}

    // Функция для добавления нового элемента в конец списка
    void append(int value) {
        if (head == nullptr) {
            head = new ListNode(value);
        } else {
            ListNode *current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new ListNode(value);
        }
    }

    // Функция для вывода всех элементов списка
    void print() {
        ListNode *current = head;
        while (current != nullptr) {
            std::cout << current->value << " -> ";
            current = current->next;
        }
        std::cout << "null" << std::endl;
    }
};

//ЗАДАНИЕ 4
class TrieNode {
public:
    bool isEndOfWord;
    std::unordered_map<char, TrieNode*> children;

    TrieNode() : isEndOfWord(false) {}

    // Деструктор для освобождения памяти
    ~TrieNode() {
        for (auto pair : children) {
            delete pair.second;
        }
    }
};

// Класс для префиксного дерева
class Trie {
public:
    TrieNode *root;

    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    // Вставка слова в префиксное дерево
    void insert(const std::string &word) {
        TrieNode *node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
    }

    // Функция для проверки, содержится ли слово в префиксном дереве
    bool search(const std::string &word) {
        TrieNode *node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return node != nullptr && node->isEndOfWord;
    }
};


int main() {
    //ЗАДАНИЕ 1
    BinarySearchTree bst;

    bst.insert(8);
    bst.insert(3);
    bst.insert(10);
    bst.insert(1);
    bst.insert(6);
    bst.insert(14);
    bst.insert(4);
    bst.insert(7);
    bst.insert(13);

    std::cout << "Сколько раз содержится в структуре число 10: " << bst.contains(10) << std::endl;
    std::cout << "Сколько раз содержится в структуре число 5: " << bst.contains(5) << std::endl;

    std::cout << "-------" << std::endl;
    //ЗАДАНИЕ 2
    MaxHeap heap;

    // Заполнение кучки значениями
    heap.insert(3);
    heap.insert(1);
    heap.insert(6);
    heap.insert(5);
    heap.insert(2);
    heap.insert(4);

    // проверка наличия элемента
    std::cout << "Сколько раз содержится в структуре число 6: " << heap.contains(6) << std::endl;
    std::cout << "Сколько раз содержится в структуре число 10: " << heap.contains(10) << std::endl;

    // удаление максимального элемента
    std::cout << "Максимальный элемент: " << heap.extractMax() << std::endl;
    std::cout << "-------" << std::endl;

    //ЗАДАНИЕ 3

    LinkedList list;

    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    list.print();
    std::cout << "-------" << std::endl;

    //ЗАДАНИЕ 4
    Trie trie;

    // Заполнение префиксного дерева словами
    trie.insert("java");
    trie.insert("script");
    trie.insert("stripe");
    trie.insert("python");
    trie.insert("c++");
    trie.insert("ruby");

    // Проверка наличия слов в префиксном дереве
    std::cout << "Содержит 'java': " << trie.search("java") << std::endl;
    std::cout << "Содержит 'script': " << trie.search("script") << std::endl;
    std::cout << "Содержит 'forever': " << trie.search("forever") << std::endl;
    return 0;
}