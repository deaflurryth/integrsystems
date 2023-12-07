//
// Created by deaflurryth ¿ on 16.11.2023.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <random>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <sstream>
//ЗАДАНИЕ 1
class Matrix {
private:
    std::vector<std::vector<int> > data;
    int rows, cols;

public:
    // конструктор
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data.resize(rows, std::vector<int>(cols, 0));
    }

    // метод для установки значений матрицы
    void set(int row, int col, int value) {
        data[row][col] = value;
    }

    // сложение матриц
    Matrix add(const Matrix &other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // вычитание матриц
    Matrix subtract(const Matrix &other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // умножение матрицы на число
    Matrix multiply(int number) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] * number;
            }
        }
        return result;
    }

    // умножение матриц
    Matrix multiply(const Matrix &other) const {
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // транспонирование матрицы
    Matrix transpose() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }

    // возведение матрицы в степень
    Matrix power(int exponent) const {
        Matrix result = *this;
        Matrix temp = *this;
        for (int i = 1; i < exponent; i++) {
            result = result.multiply(temp);
        }
        return result;
    }

    // вывод матрицы
    void print() const {
        for (const auto &row : data) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }
};
//ЗАДАНИЕ 2
class Vector {
private:
    double x, y, z;

public:
    // конструктор с параметрами
    Vector(double x, double y, double z) : x(x), y(y), z(z) {}

    // метод для вычисления длины вектора
    double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // метод для вычисления скалярного произведения
    double dot(const Vector &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // метод для вычисления векторного произведения
    Vector cross(const Vector &other) const {
        return Vector(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
        );
    }

    // метод для вычисления косинуса угла между векторами
    double angle(const Vector &other) const {
        return dot(other) / (length() * other.length());
    }

    // метод для суммы векторов
    Vector operator+(const Vector &other) const {
        return Vector(x + other.x, y + other.y, z + other.z);
    }

    // метод для разности векторов
    Vector operator-(const Vector &other) const {
        return Vector(x - other.x, y - other.y, z - other.z);
    }

    // статический метод для генерации массива случайных векторов
    static std::vector<Vector> generateRandomVectors(int N) {
        std::vector<Vector> vectors;
        for (int i = 0; i < N; i++) {
            vectors.push_back(Vector(
                    static_cast<double>(rand()) / RAND_MAX,
                    static_cast<double>(rand()) / RAND_MAX,
                    static_cast<double>(rand()) / RAND_MAX
            ));
        }
        return vectors;
    }

    // метод для вывода вектора
    void print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
    }
};
//ЗАДАНИЕ 3 + 4
// абстрактный базовый класс Shape
class Shape {
public:
    // чисто виртуальная функция для получения объема
    virtual double getVolume() const = 0;

    // виртуальный деструктор необходим для корректного удаления производных объектов
    virtual ~Shape() {}
};

class SolidOfRevolution : public Shape {
protected:
    double radius;

public:
    SolidOfRevolution(double r) : radius(r) {}

    double getRadius() const { return radius; }
};

class Cylinder : public SolidOfRevolution {
private:
    double height;

public:
    Cylinder(double r, double h) : SolidOfRevolution(r), height(h) {}

    double getVolume() const override { return 3.14159 * radius * radius * height; }
};

class Ball : public SolidOfRevolution {
public:
    Ball(double r) : SolidOfRevolution(r) {}

    double getVolume() const override { return (4.0 / 3.0) * 3.14159 * radius * radius * radius; }
};

class Pyramid : public Shape {
private:
    double baseArea;
    double height;

public:
    Pyramid(double b, double h) : baseArea(b), height(h) {}

    double getVolume() const override { return (baseArea * height) / 3.0; }
};

class Box : public Shape {
private:
    std::vector<Shape*> shapes;
    double capacity;
    double volume;

public:
    Box(double c) : capacity(c), volume(0) {}

    double getVolume() const override { return volume; }

    bool add(Shape* shape) {
        double totalVolume = volume + shape->getVolume();
        if (totalVolume <= capacity) {
            shapes.push_back(shape);
            volume = totalVolume;
            return true;
        } else {
            return false;
        }
    }

    // деструктор для освобождения памяти
    ~Box() {
        for (Shape* shape : shapes) {
            delete shape;
        }
    }
};
//ЗАДАНИЕ 5
class WeightedRandomSelector {
private:
    std::vector<int> values;
    std::vector<double> weights;
    std::discrete_distribution<> distribution;

public:
    // конструктор, который принимает два массива
    WeightedRandomSelector(const std::vector<int>& values, const std::vector<double>& weights)
            : values(values), weights(weights) {
        // создаем распределение на основе весов
        distribution = std::discrete_distribution<>(weights.begin(), weights.end());
    }

    // метод для получения случайного значения с учетом веса
    int getRandomValue() {
        // генератор случайных чисел
        std::random_device rd;
        std::mt19937 gen(rd());
        // получаем индекс в соответствии с весами
        int index = distribution(gen);
        // возвращаем значение
        return values[index];
    }
};

//ЗАДАНИЕ 6
class Tiles {
public:
    std::string brand;
    int size_h;
    int size_w;
    double price;

    // метод для отображения данных о плитке
    void getData() {
        std::cout << "Brand: " << brand << std::endl;
        std::cout << "Height: " << size_h << " cm" << std::endl;
        std::cout << "Width: " << size_w << " cm" << std::endl;
        std::cout << "Price: $" << price << std::endl;
    }
};

//ЗАДАНИЕ 7
class Children {
private:
    std::string name;
    std::string surname;
    int age;

public:
    // метод для ввода данных о ребенке
    void setData(const std::string& name, const std::string& surname, int age) {
        this->name = name;
        this->surname = surname;
        this->age = age;
    }

    // метод для отображения данных о ребенке
    void displayData() {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Surname: " << surname << std::endl;
        std::cout << "Age: " << age << std::endl;
    }
};

//ЗАДАНИЕ 8
class Matrixx {
private:
    std::vector<std::vector<int> > data;

public:
    // конструктор для инициализации матрицы определенного размера
    Matrixx(int rows, int cols) : data(rows, std::vector<int>(cols)) {}

    // метод для заполнения матрицы значениями
    void fillMatrix() {
        for (int i = 0; i < data.size(); ++i) {
            for (int j = 0; j < data[i].size(); ++j) {
                data[i][j] = (i + 1) * 10 + (j + 1); // примерное заполнение для демонстрации
            }
        }
    }

    // метод для транспонирования матрицы
    void transpose() {
        std::vector<std::vector<int> > transposed(data[0].size(), std::vector<int>(data.size()));
        for (int i = 0; i < data.size(); ++i) {
            for (int j = 0; j < data[i].size(); ++j) {
                transposed[j][i] = data[i][j];
            }
        }
        data = transposed; // заменяем исходную матрицу транспонированной
    }

    // метод для отображения матрицы
    void display() {
        for (const auto &row : data) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }
};

//ЗАДАНИЕ 9
// абстрактный базовый класс Employee
class Employee {
protected:
    std::string id;
    std::string name;

public:
    Employee(const std::string& id, const std::string& name) : id(id), name(name) {}
    virtual double calculateMonthlySalary() const = 0;
    std::string getName() const { return name; }
    std::string getId() const { return id; }
};

// класс для работников с почасовой оплатой
class HourlyEmployee : public Employee {
private:
    double hourlyRate;

public:
    HourlyEmployee(const std::string& id, const std::string& name, double hourlyRate)
            : Employee(id, name), hourlyRate(hourlyRate) {}

    double calculateMonthlySalary() const override {
        return 20.8 * 8 * hourlyRate;
    }
};

// класс для работников с фиксированной оплатой
class FixedPayEmployee : public Employee {
private:
    double fixedMonthlyPay;

public:
    FixedPayEmployee(const std::string& id, const std::string& name, double fixedMonthlyPay)
            : Employee(id, name), fixedMonthlyPay(fixedMonthlyPay) {}

    double calculateMonthlySalary() const override {
        return fixedMonthlyPay;
    }
};

// функция для сравнения двух сотрудников
bool compareEmployees(const Employee* lhs, const Employee* rhs) {
    if (lhs->calculateMonthlySalary() == rhs->calculateMonthlySalary())
        return lhs->getName() < rhs->getName();
    return lhs->calculateMonthlySalary() > rhs->calculateMonthlySalary();
}
int main() {
    //ЗАДАНИЕ 1
    Matrix mat1(3, 3);
    Matrix mat2(3, 3);
    Matrix sum = mat1.add(mat2);
    Matrix diff = mat1.subtract(mat2);
    Matrix prod = mat1.multiply(mat2);
    sum.print();
    diff.print();
    prod.print();

    //ЗАДАНИЕ 2
    Vector v1(1.0, 2.0, 3.0);
    Vector v2(4.0, 5.0, 6.0);

    // Вычисление длины вектора
    std::cout << "Длина v1: " << v1.length() << std::endl;
    std::cout << "Точка двух векторов v1 и v2: " << v1.dot(v2) << std::endl;

    // Вычисление векторного произведения
    Vector vCross = v1.cross(v2);
    std::cout << "Перекрестие v1 и v2: ";
    vCross.print();

    // Вычисление угла (в косинусах) между векторами
    double cosAngle = v1.angle(v2);
    std::cout << "Косинусное между v1 и v2: " << cosAngle << std::endl;

    // Сумма векторов
    Vector vSum = v1 + v2;
    std::cout << "Сумма v1 и v2: ";
    vSum.print();

    // Разность векторов
    Vector vDiff = v1 - v2;
    std::cout << "Разница между v1 и v2: ";
    vDiff.print();
    int N = 5;
    std::vector<Vector> randomVectors = Vector::generateRandomVectors(N);
    std::cout << "Массив " << N << " случайных векторов:" << std::endl;
    for (const Vector& randomVector : randomVectors) {
        randomVector.print();
    }

    //ЗАДАНИЕ 3 + 4
    Box box(1000); // Объем контейнера
    Cylinder cylinder(10, 20);
    Ball ball(15);
    Pyramid pyramid(100, 30);

    std::cout << "Попытка добавить Cylinder: " << box.add(&cylinder) << std::endl;
    std::cout << "Попытка добавить Ball: " << box.add(&ball) << std::endl;
    std::cout << "Попытка добавить Pyramid: " << box.add(&pyramid) << std::endl;

    //ЗАДАНИЕ 5
    std::vector<int> values;
    values.push_back(1);
    values.push_back(2);
    values.push_back(3);

    std::vector<double> weights;
    weights.push_back(1);
    weights.push_back(2);
    weights.push_back(10);
    WeightedRandomSelector selector(values, weights);

    std::cout << "Случайное число: " << selector.getRandomValue() << std::endl;

    //ЗАДАНИЕ 6
    Tiles tile1, tile2;

    // внесение данных в поля первого объекта
    tile1.brand = "BrandA";
    tile1.size_h = 30;
    tile1.size_w = 20;
    tile1.price = 25.50;

    // внесение данных в поля второго объекта
    tile2.brand = "BrandB";
    tile2.size_h = 25;
    tile2.size_w = 30;
    tile2.price = 35.75;

    // отображение данных о плитках
    std::cout << "Tile 1 Data:" << std::endl;
    tile1.getData();
    std::cout << std::endl;

    std::cout << "Tile 2 Data:" << std::endl;
    tile2.getData();

    //ЗАДАНИЕ 7
    Children child1, child2;

    // Внесение данных в первый объект
    child1.setData("Ivan", "Ivanov", 10);

    // Внесение данных во второй объект
    child2.setData("Maria", "Petrova", 8);

    // Отображение данных о детях
    std::cout << "Child 1 Data:" << std::endl;
    child1.displayData();
    std::cout << std::endl;

    std::cout << "Child 2 Data:" << std::endl;
    child2.displayData();

    //ЗАДАНИЕ 8
    Matrixx matrix(4, 2); // Создание матрицы 4x2
    matrix.fillMatrix(); // Заполнение матрицы значениями
    std::cout << "Изначальная матрица:" << std::endl;
    matrix.display(); // Отображение исходной матрицы

    matrix.transpose(); // Транспонирование матрицы
    std::cout << "Транспанированая матрица:" << std::endl;
    matrix.display(); // Отображение транспонированной матрицы

    //ЗАДАНИЕ 10
    std::vector<Employee*> employees;

    // Пример добавления работников
    employees.push_back(new HourlyEmployee("1", "Степан", 50));
    employees.push_back(new FixedPayEmployee("2", "Михаил", 5000));

    // a) Сортировка по убыванию среднемесячной зарплаты
    std::sort(employees.begin(), employees.end(), compareEmployees);

    // Вывод информации о работниках
    for (const auto& emp : employees) {
        std::cout << "ID: " << emp->getId() << ", Name: " << emp->getName()
                  << ", Monthly Salary: " << emp->calculateMonthlySalary() << std::endl;
    }

    // b) Вывод первых 5 имен работников
    for (int i = 0; i < 5 && i < employees.size(); ++i) {
        std::cout << employees[i]->getName() << std::endl;
    }

    // c) Вывод последних 3 идентификаторов работников
    for (int i = employees.size() - 3; i < employees.size(); ++i) {
        std::cout << employees[i]->getId() << std::endl;
    }

    // d) Запись в файл
    std::ofstream outFile("employees.txt");
    for (const auto& emp : employees) {
        outFile << emp->getId() << "," << emp->getName() << "," << emp->calculateMonthlySalary() << std::endl;
    }
    outFile.close();

    // e) Чтение из файла и обработка некорректного формата
    std::ifstream inFile("employees.txt");
    std::string line, id, name, salaryStr;
    double salary;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        if (std::getline(iss, id, ',') && std::getline(iss, name, ',') && std::getline(iss, salaryStr)) {
            try {
                salary = std::stod(salaryStr);
                // Обработка данных...
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid format in file: " << e.what() << std::endl;
            }
        }
    }
    inFile.close();

    // Очистка выделенной памяти
    for (auto& emp : employees) {
        delete emp;
    }

    return 0
    ;
};