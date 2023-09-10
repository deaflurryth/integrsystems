#include <iostream>
#include <cmath>

using namespace std;

bool isPrime(int num) {
    if (num <= 1) {
        return false; // 1 и отрицательные числа не являются простыми
    }
    if (num <= 3) {
        return true; // 2 и 3  простые числа
    }
    if (num % 2 == 0 || num % 3 == 0) {
        return false; // числа кратные 2 или 3, не являются простыми
    }
    //  делители до квадратного корня из числа
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

bool isPowerOf22(int N) {
    // является ли N положительным и больше 1
    if (N <= 0 || N == 1) {
        return false;
    }

    // делится ли N на 22 и оставляет ли остаток 0
    while (N % 22 == 0) {
        N /= 22;
    }

    // если после деления N не равно 1, то это не степень 22
    return N == 1;
}

void printDigitsInReverse(int N) { //возвращаемый тип функции, без возврата значения
    if (N == 0) {
        return; //  N стало равным 0, завершение
    }

    // вывод последней цифры числа N
    std::cout << N % 10;

    // рекурсивно вызываем функцию для оставшихся цифр числа N
    printDigitsInReverse(N / 10);
}

int nod(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}



int main() {
    //1
    printf("#1\n");
    int a= 12;
    int b= 600;
    int temp= a;
    a= b;
    b= temp;
    std::cout<< "a = " << a<< std::endl;
    std::cout<< "b = " << b<< std::endl;

    //2
    printf("----\n#2\n");
    double c= 120.0;
    double d= 90.0;
    double e= sqrt(a * a + b * b);
    std::cout<< "Длина гипотенузы равна: " << e << std::endl;

    //3
    printf("----\n#3\n");
    int number= 155; //но это легко сломать, если ввести 1212121212126 условно
    std::cout<< number% 10<< std::endl;

    //4
    printf("----\n#4\n");
    int secondnum= 225;
    std::cout<< (secondnum/ 10) % 10<< std::endl;

    //5
    printf("----\n#5\n");
    int thirdnum= 45;
    std::cout<< thirdnum/10<< std::endl;

    //6
    printf("----\n#6\n");
    int num1, num2;
    std::cout << "Введите первое целое число: ";
    std::cin >> num1;
    std::cout << "Введите второе целое число: ";
    std::cin >> num2;
    std::cout << "Среднее арифметическое: " << (num1 + num2)/2 << std::endl;

    //7
    printf("----\n#7\n");
    int num3, num4;
    std::cout << "Введите первое целое число: ";
    std::cin >> num3;
    std::cout << "Введите второе целое число: ";
    std::cin >> num4;
    std::cout << "Среднее геометрическое: " << sqrt(num3*num4) << std::endl;

    //8
    printf("----\n#8\n");
    double x1, y1, x2, y2;
    std::cout << "(x1 y1): ";
    std::cin >> x1 >> y1;
    std::cout << "(x2 y2): ";
    std::cin >> x2 >> y2;
    double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    std::cout << "Расстояние между точками: " << distance << std::endl;

    //9
    printf("----\n#9\n");
    double f, s, t;
    std::cout << "Введите первое, второе и третье число: ";
    std::cin >> f >> s >> t;
    double middle;
    if ((f < s && s < t) || (t < s && s < f)) {
        middle = s;
    } else if ((s < f && f < t) || (t < f && f < s)) {
        middle = f;
    } else {
        middle = t;
    }
    std::cout << "Среднее число: " << middle << std::endl;

    //10
    printf("----\n#10\n");
    double aa, bb, cc;
    std::cout << "Введите a, b и c: ";
    std::cin >> aa >> bb >> cc;
    double discrit= bb* bb- 4* aa* cc;
    if (discrit > 0) {
        double root1 = (-bb + sqrt(discrit)) / (2 * aa);
        double root2 = (-bb - sqrt(discrit)) / (2 * aa);
        std::cout << "Корень 1: " << root1 << std::endl;
        std::cout << "Корень 2: " << root2 << std::endl;
    } else if (discrit == 0) {
        double rootsqrt = -bb / (2 * aa);
        std::cout << "Уравнение имеет один корень: " << rootsqrt << std::endl;
    } else {
        std::cout << "Корней нет." << std::endl;
    }

    //11
    printf("----\n#11\n");
    double t1, t2, t3;
    std::cout << "Введите t1, t2 и t3: ";
    std::cin >> t1 >> t2 >> t3;
    double maxed;
    if (t1 > t2 && t1 > t3) {
        maxed = t1;
    } else if (t2 > t1 && t2 > t3) {
        maxed = t2;
    } else {
        maxed = t3;
    }
    std::cout << "Максимальное число: " << maxed << std::endl;

    //12
    printf("----\n#12\n");
    double nums1, nums2, nums3;
    std::cout << "Введите длины трех отрезков: ";
    std::cin >> nums1 >> nums2 >> nums3;
    if (nums1 + nums2 > nums3 && nums1 + nums3 > nums2 && nums2 + nums3 > nums1) {
        if (nums1 == nums2 && nums2 == nums3) {
            std::cout << "Треугольник равносторонний" << std::endl;
        } else if (nums1 == nums2 || nums2 == nums3 || nums1 == nums3) {
            std::cout << "Треугольник равнобедренный" << std::endl;
        } else {
            std::cout << "Треугольник разносторонний" << std::endl;
        }
    } else {
        std::cout << "Треугольника не существует" << std::endl;
    }

    //13
    printf("----\n#13\n");
    double toch1, toch2;
    std::cout << "Введите точки 1 и 2: ";
    std::cin >> toch1 >> toch2;
    if (toch1 > 0 && toch2 > 0) {
        std::cout << "Точка принадлежит I четверти" << std::endl;
    } else if (toch1 < 0 && toch2 > 0) {
        std::cout << "Точка принадлежит II четверти" << std::endl;
    } else if (toch1 < 0 && toch2 < 0) {
        std::cout << "Точка принадлежит III четверти" << std::endl;
    } else if (toch1 > 0 && toch2 < 0) {
        std::cout << "Точка принадлежит IV четверти" << std::endl;
    } else if (toch1 == 0 && toch2 == 0) {
        std::cout << "Точка находится в начале координат" << std::endl;
    } else if (toch1 == 0) {
        std::cout << "Точка лежит на оси X" << std::endl;
    } else {
        std::cout << "Точка лежит на оси Y" << std::endl;
    }

    //14
    printf("----\n#14\n");
    int n;
    std::cout << "Введите число n: ";
    std::cin >> n;
    int result14 = 1;
    while (n > 0) {
        result14 *= n;
        n -= 2;
    }
    std::cout << "Двойной факториал: " << result14 << std::endl;

    //15
    printf("----\n#15\n");
    int n2;
    std::cout << "Введите число n: ";
    std::cin >> n2;
    int result15 = 1;
    for (int i = n2; i > 0; i -= 2) {
        result15 *= i;
    }
    std::cout << "Двойной факториал: " << result15 << std::endl;

    //16
    printf("----\n#16\n");
    int aaa, bbb;
    std::cout << "Введите интервал [a, b]: ";
    std::cin >> aaa >> bbb;
    if (aaa <= 2) {
        std::cout << "Простые числа в интервале [" << 2 << ", " << bbb << "]: 2 ";
    }
    for (int i = (aaa % 2 == 0 ? aaa + 1 : aaa); i <= bbb; i += 2) {
        if (isPrime(i)) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;

    //17
    printf("----\n#17\n");
    int numberz;
    int sum = 0;
    std::cout << "Введите последовательность чисел, закончите ввод числом -9999:" << std::endl;
    while (true) {
        std::cin >> numberz;
        if (numberz == -9999) {
            break;
        }
        std::cout << "Прочитано число: " << numberz << std::endl;
        sum += numberz;
    }
    std::cout << "Сумма всех элементов последовательности (без -9999): " << sum << std::endl;

    //18
    printf("----\n#18\n");
    int number18;
    int min = INT_MAX;
    int max = INT_MIN;
    std::cout << "Введите последовательность чисел, оканчивающуюся нулём:" << std::endl;
    while (true) {
        std::cin >> number18;
        if (number18 == 0) {
            break;
        }
        if (number > max) {
            max = number18;
        }
        if (number < min) {
            min = number18;
        }
    }
    if (min == INT_MAX || max == INT_MIN) {
        std::cout << "В последовательности нет чисел, отличных от нуля." << std::endl;
    } else {
        std::cout << "Минимальное значение: " << min << std::endl;
        std::cout << "Максимальное значение: " << max << std::endl;
    }

    //19
    printf("----\n#19\n");
    int N;
    std::cout << "Введите число N: ";
    std::cin >> N;
    int item = 1;
    int squareitem = item * item;
    std::cout << "Точные квадраты натуральных чисел, не превосходящие " << N << ":" << std::endl;
    while (squareitem <= N) {
        std::cout << squareitem << " ";
        item++;
        squareitem = item * item;
    }
    std::cout << std::endl;

    //20
    printf("----\n#20\n");
    if (isPowerOf22(N)) {
        std::cout << N << " является степенью числа 22" << std::endl;
    } else {
        std::cout << N << " не является степенью числа 22" << std::endl;
    }

    //21
    printf("----\n#21\n");
    if (N < 0) {
        std::cout << "Число должно быть натуральным" << std::endl;
        return 1;
    }
    std::cout << "Цифры числа " << N << " в обратном порядке: ";
    printDigitsInReverse(N);
    std::cout << std::endl;

    //22
    printf("----\n#22\n");
    int number1, number2;
    std::cout << "Введите два положительных целых числа: ";
    std::cin >> number1 >> number2;

    if (number1 <= 0 || number2 <= 0) {
        std::cout << "Числа должны быть положительными." << std::endl;
        return 1;
    }

    int result22 = nod(number1, number1);
    std::cout << "Наибольший общий делитель (НОД) чисел " << number1 << " и " << number2 << " = " << result22 << std::endl;

    //23
    printf("----\n#23\n");
    int mark;
    std::cout << "Введите школьную оценку (1-5): ";
    std::cin >> mark;
    std::string description;
    switch (mark) {
        case 1:
            description = "плохо";
            break;
        case 2:
            description = "неудовлетворительно";
            break;
        case 3:
            description = "удовлетворительно";
            break;
        case 4:
            description = "хорошо";
            break;
        case 5:
            description = "отлично";
            break;
        default:
            description = "чет не то ввели";
            break;
    }
    std::cout << "Словесное описание оценки: " << description << std::endl;

    //24
    printf("----\n#24\n");
}

