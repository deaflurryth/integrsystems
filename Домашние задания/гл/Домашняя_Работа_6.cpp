#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <random>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <sstream>

// Используем понятные названия и современные подходы
// Матричный калькулятор
class MatrixCalculator {
private:
    std::vector<std::vector<int>> elements;
    int rowCount, columnCount;

public:
    // Использование конструктора с инициализатором списков
    MatrixCalculator(int rows, int cols) : rowCount(rows), columnCount(cols), elements(rows, std::vector<int>(cols, 0)) {}

    // Установка элемента матрицы
    void setElement(int row, int col, int value) {
        if (row >= 0 && row < rowCount && col >= 0 && col < columnCount) {
            elements[row][col] = value;
        }
    }

    // Операции над матрицами
    MatrixCalculator add(const MatrixCalculator& other) const;
    MatrixCalculator subtract(const MatrixCalculator& other) const;
    MatrixCalculator multiply(int scalar) const;
    MatrixCalculator multiply(const MatrixCalculator& other) const;
    MatrixCalculator transpose() const;
    MatrixCalculator power(int exponent) const;

    // Вывод матрицы
    void display() const;
};

// Класс для работы с векторами в трехмерном пространстве
class Vector3D {
private:
    double x, y, z;

public:
    Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

    double calculateLength() const;
    double dotProduct(const Vector3D& other) const;
    Vector3D crossProduct(const Vector3D& other) const;
    double calculateAngle(const Vector3D& other) const;

    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;

    static std::vector<Vector3D> generateRandomVectors(int count);
    void display() const;
};

// Формы и контейнеры
class Shape {
public:
    virtual double calculateVolume() const = 0;
    virtual ~Shape() {}
};

class SolidOfRevolution : public Shape {
protected:
    double radius;

public:
    SolidOfRevolution(double radius) : radius(radius) {}
    double getRadius() const { return radius; }
};

class Cylinder : public SolidOfRevolution {
private:
    double height;

public:
    Cylinder(double radius, double height) : SolidOfRevolution(radius), height(height) {}
    double calculateVolume() const override;
};

class Ball : public SolidOfRevolution {
public:
    Ball(double radius) : SolidOfRevolution(radius) {}
    double calculateVolume() const override;
};

class Pyramid : public Shape {
private:
    double baseArea, height;

public:
    Pyramid(double baseArea, double height) : baseArea(baseArea), height(height) {}
    double calculateVolume() const override;
};

class Box : public Shape {
private:
    std::vector<Shape*> storedShapes;
    double capacity, currentVolume;

public:
    Box(double capacity) : capacity(capacity), currentVolume(0) {}
    ~Box();
    bool addShape(Shape* shape);
    double calculateVolume() const override;
};

// Продвинутый рандомизатор с весами
class WeightedRandomizer {
private:
    std::vector<int> elements;
    std::vector<double> weights;
    std::discrete_distribution<> dist;

public:
    WeightedRandomizer(const std::vector<int>& elements, const std::vector<double>& weights);
    int getRandomElement();
};

// Информация о плитке
class TileInfo {
public:
    std::string brand;
    int height, width;
    double price;

    void displayInfo() const;
};

// Информация о детях
class ChildInfo {
private:
    std::string firstName, lastName;
    int age;

public:
    void setInfo(const std::string& firstName, const std::string& lastName, int age);
    void displayInfo() const;
};

// Матричный транспонер
class MatrixTransposer {
private:
    std::vector<std::vector<int>> matrix;

public:
    MatrixTransposer(int rows, int cols);
    void fillWithSampleData();
    void transpose();
    void display() const;
};

// Сотрудник и его зарплата
class Employee {
protected:
    std::string id, fullName;

public:
    Employee(const std::string& id, const std::string& fullName) : id(id), fullName(fullName) {}
    virtual double calculateMonthlySalary() const = 0;

    std::string getName() const { return fullName; }
    std::string getId() const { return id; }
};

class HourlyEmployee : public Employee {
private:
    double hourlyRate;

public:
    HourlyEmployee(const std::string& id, const std::string& name, double hourlyRate)
            : Employee(id, name), hourlyRate(hourlyRate) {}

    double calculateMonthlySalary() const override;
};

class FixedPayEmployee : public Employee {
private:
    double fixedMonthlyPay;

public:
    FixedPayEmployee(const std::string& id, const std::string& name, double fixedMonthlyPay)
            : Employee(id, name), fixedMonthlyPay(fixedMonthlyPay) {}

    double calculateMonthlySalary() const override;
};

bool compareEmployees(const Employee* lhs, const Employee* rhs);

int main() {
    // ЗАДАНИЕ 1: Работа с матрицами
    MatrixCalculator mat1(3, 3);
    MatrixCalculator mat2(3, 3);
    MatrixCalculator sum = mat1.add(mat2);
    MatrixCalculator diff = mat1.subtract(mat2);
    MatrixCalculator prod = mat1.multiply(mat2);

    sum.display();
    diff.display();
    prod.display();

    // ЗАДАНИЕ 2: Операции с векторами
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);

    std::cout << "Длина v1: " << v1.calculateLength() << std::endl;
    std::cout << "Скалярное произведение v1 и v2: " << v1.dotProduct(v2) << std::endl;

    Vector3D vCross = v1.crossProduct(v2);
    std::cout << "Векторное произведение v1 и v2: ";
    vCross.display();

    double cosAngle = v1.calculateAngle(v2);
    std::cout << "Косинус угла между v1 и v2: " << cosAngle << std::endl;

    Vector3D vSum = v1 + v2;
    std::cout << "Сумма v1 и v2: ";
    vSum.display();

    Vector3D vDiff = v1 - v2;
    std::cout << "Разность между v1 и v2: ";
    vDiff.display();

    // ЗАДАНИЕ 3 + 4: Формы и контейнеры
    Box box(1000); // Объем контейнера
    Cylinder cylinder(10, 20);
    Ball ball(15);
    Pyramid pyramid(100, 30);

    std::cout << "Добавление цилиндра: " << box.addShape(&cylinder) << std::endl;
    std::cout << "Добавление шара: " << box.addShape(&ball) << std::endl;
    std::cout << "Добавление пирамиды: " << box.addShape(&pyramid) << std::endl;

    // ЗАДАНИЕ 5: Взвешенный случайный выбор
    WeightedRandomizer selector({1, 2, 3}, {1.0, 2.0, 10.0});
    std::cout << "Случайный выбор: " << selector.getRandomElement() << std::endl;

    // ЗАДАНИЕ 6: Информация о плитке
    TileInfo tile1{"BrandA", 30, 20, 25.50};
    TileInfo tile2{"BrandB", 25, 30, 35.75};

    tile1.displayInfo();
    tile2.displayInfo();

    // ЗАДАНИЕ 7: Информация о детях
    ChildInfo child1, child2;
    child1.setInfo("Test", "1", 10);
    child2.setInfo("Overtest", "2", 8);

    child1.displayInfo();
    child2.displayInfo();

    // ЗАДАНИЕ 8: Матричный транспонер
    MatrixTransposer matrix(4, 2);
    matrix.fillWithSampleData();

    std::cout << "Исходная матрица:" << std::endl;
    matrix.display();

    matrix.transpose();
    std::cout << "Транспонированная матрица:" << std::endl;
    matrix.display();

    // ЗАДАНИЕ 10: Сотрудники и их зарплаты
    std::vector<Employee*> employees;
    employees.push_back(new HourlyEmployee("1", "Степан", 50.0));
    employees.push_back(new FixedPayEmployee("2", "Михаил", 5000.0));

    std::sort(employees.begin(), employees.end(), compareEmployees);

    for (const auto& emp : employees) {
        std::cout << "ID: " << emp->getId() << ", Имя: " << emp->getName()
                  << ", Зарплата в месяц: " << emp->calculateMonthlySalary() << std::endl;
    }

    // Очистка памяти
    for (auto& emp : employees) {
        delete emp;
    }

    return 0;
}

