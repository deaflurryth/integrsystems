№1 Реализовать функцию, которая возвращает единичную квадратную матрицу заданного размера.

#include <stdio.h>
#include <stdlib.h>

// Функция для создания и заполнения единичной матрицы
double** createIdentityMatrix(int size) {
    // Выделение памяти под двумерный массив (матрицу)
    double** matrix = (double**)malloc(size * sizeof(double*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (double*)malloc(size * sizeof(double));
    }

    // Заполнение матрицы значениями
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                matrix[i][j] = 1.0; // Главная диагональ - единицы
            } else {
                matrix[i][j] = 0.0; // Остальные элементы - нули
            }
        }
    }

    return matrix;
}

int main() {
    int size = 3; // Задаем размер квадратной матрицы

    // Вызываем функцию для создания единичной матрицы
    double** identityMatrix = createIdentityMatrix(size);

    // Выводим матрицу на экран
    printf("Единичная матрица %dx%d:\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%f ", identityMatrix[i][j]);
        }
        printf("\n");
    }

    // Освобождаем выделенную память
    for (int i = 0; i < size; i++) {
        free(identityMatrix[i]);
    }
    free(identityMatrix);

    return 0;
}


№3	Реализовать функцию, которая на вход получает одномерный массив и булевскую переменную. Функция возвращает массив той же размерности, и отсортированной 
в зависимости от булевской переменной (true – по возрастанию, false – по убыванию)
#include <stdio.h>
#include <stdbool.h>

// Функция для сравнения элементов при сортировке
int compare(const void *a, const void *b) {
    int intA = *((int*)a);
    int intB = *((int*)b);

    return intA - intB;
}

// Функция для сортировки массива в зависимости от булевской переменной
int* sortArray(int* arr, int size, bool ascending) {
    // Создаем копию исходного массива
    int* sortedArr = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        sortedArr[i] = arr[i];
    }

    // Используем стандартную функцию qsort для сортировки
    if (ascending) {
        qsort(sortedArr, size, sizeof(int), compare);
    } else {
        qsort(sortedArr, size, sizeof(int), compare);
        // Реверсируем массив для убывающей сортировки
        int temp;
        for (int i = 0; i < size / 2; i++) {
            temp = sortedArr[i];
            sortedArr[i] = sortedArr[size - 1 - i];
            sortedArr[size - 1 - i] = temp;
        }
    }

    return sortedArr;
}

int main() {
    int size = 5;
    int arr[] = {3, 1, 4, 1, 5};
    bool ascending = true;

    int* sortedArr = sortArray(arr, size, ascending);

    printf("Отсортированный массив:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", sortedArr[i]);
    }
    printf("\n");

    // Освобождаем память после использования
    free(sortedArr);

    return 0;
}



№4 Дано натуральное число n. Выведите все числа от 1 до n. Реализовать при помощи рекурсии.
#include <stdio.h>

// Функция для вывода чисел от 1 до n с использованием рекурсии
void printNumbers(int n) {
    if (n > 0) {
        printNumbers(n - 1); // Рекурсивный вызов для числа n-1
        printf("%d ", n);    // Вывод числа n после рекурсии
    }
}

int main() {
    int n;

    printf("Введите натуральное число n: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Число должно быть натуральным.\n");
    } else {
        printf("Числа от 1 до %d: ", n);
        printNumbers(n);
        printf("\n");
    }

    return 0;
}


№5 Напишите функцию, которая проверяет, входит ли в одномерный массив заданный элемент или нет. Используйте перебор и двоичный поиск 
для решения этой задачи. Сравните время выполнения обоих решений для больших массивов (например, 100000000 элементов). Реализовать при помощи рекурсии

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для перебора элементов в массиве
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i; // Найден элемент, возвращаем индекс
        }
    }
    return -1; // Элемент не найден
}

// Функция для двоичного поиска элемента в отсортированном массиве
int binarySearch(int arr[], int left, int right, int target) {
    if (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid; // Найден элемент, возвращаем индекс
        }
        
        if (arr[mid] > target) {
            return binarySearch(arr, left, mid - 1, target); // Рекурсивный поиск в левой половине
        }
        
        return binarySearch(arr, mid + 1, right, target); // Рекурсивный поиск в правой половине
    }
    
    return -1; // Элемент не найден
}

int main() {
    const int size = 100000000; // Размер массива
    int* arr = (int*)malloc(size * sizeof(int));

    // Заполняем массив случайными числами и сортируем его
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }

    int target = size - 1; // Элемент, который будем искать

    // Измеряем время выполнения линейного поиска
    clock_t start = clock();
    int linearResult = linearSearch(arr, size, target);
    clock_t end = clock();
    double linearTime = (double)(end - start) / CLOCKS_PER_SEC;

    // Измеряем время выполнения двоичного поиска
    start = clock();
    int binaryResult = binarySearch(arr, 0, size - 1, target);
    end = clock();
    double binaryTime = (double)(end - start) / CLOCKS_PER_SEC;

    if (linearResult != -1) {
        printf("Линейный поиск: Элемент %d найден на индексе %d, время выполнения: %f сек\n", target, linearResult, linearTime);
    } else {
        printf("Линейный поиск: Элемент %d не найден, время выполнения: %f сек\n", target, linearTime);
    }

    if (binaryResult != -1) {
        printf("Двоичный поиск: Элемент %d найден на индексе %d, время выполнения: %f сек\n", target, binaryResult, binaryTime);
    } else {
        printf("Двоичный поиск: Элемент %d не найден, время выполнения: %f сек\n", target, binaryTime);
    }

    free(arr);

    return 0;
}


№6.	Найдите корень уравнения cos x5 + x4-345.3*x-23=0 на отрезке [0;10] с точностью по x не хуже 0.001. 
Известно, что на этом промежутке корень единственный. Используйте для этого метод деления отрезка пополам (и рекурсию).

#include <stdio.h>
#include <math.h>

// Функция для вычисления значения уравнения
double equation(double x) {
    return cos(pow(x, 5)) + pow(x, 4) - 345.3 * x - 23;
}

// Функция для нахождения корня уравнения методом деления отрезка пополам
double findRoot(double a, double b, double tolerance) {
    double c = (a + b) / 2.0; // Середина отрезка
    double fc = equation(c); // Значение функции в точке c

    // Если разница между a и b меньше заданной точности, возвращаем c
    if (fabs(b - a) < tolerance) {
        return c;
    }

    // Если функция в c близка к нулю, возвращаем c
    if (fabs(fc) < tolerance) {
        return c;
    }

    // Если функция в точке a и c имеет разные знаки, ищем корень в левой половине
    if (equation(a) * fc < 0) {
        return findRoot(a, c, tolerance);
    }

    // В противном случае ищем корень в правой половине
    return findRoot(c, b, tolerance);
}

int main() {
    double a = 0.0; // Левая граница отрезка
    double b = 10.0; // Правая граница отрезка
    double tolerance = 0.001; // Точность

    // Вызываем функцию для нахождения корня уравнения
    double root = findRoot(a, b, tolerance);

    printf("Корень уравнения: %lf\n", root);

    return 0;
}


№7	Найти элемент, наиболее близкий к среднему значению всех элементов массива.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функция для нахождения элемента, наиболее близкого к среднему значению
int findClosestToAverage(int arr[], int size) {
    if (size <= 0) {
        return -1; // Возвращаем -1 в случае пустого массива
    }

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }

    double average = (double)sum / size; // Среднее значение

    int closest = arr[0]; // Начинаем с первого элемента
    int minDifference = abs(arr[0] - average);

    for (int i = 1; i < size; i++) {
        int difference = abs(arr[i] - average);
        if (difference < minDifference) {
            closest = arr[i];
            minDifference = difference;
        }
    }

    return closest;
}

int main() {
    int size;
    printf("Введите размер массива: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Размер массива должен быть положительным.\n");
        return 1;
    }

    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Ошибка выделения памяти.\n");
        return 1;
    }

    printf("Введите элементы массива:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    int closest = findClosestToAverage(arr, size);

    if (closest != -1) {
        printf("Элемент, наиболее близкий к среднему значению: %d\n", closest);
    } else {
        printf("Массив пуст.\n");
    }

    free(arr);

    return 0;
}


№8	Определить, имеются ли в массиве одинаковые элементы.
#include <stdio.h>

// Функция для определения наличия одинаковых элементов в массиве
int hasDuplicates(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                return 1; // Есть повторяющиеся элементы
            }
        }
    }
    return 0; // Нет повторяющихся элементов
}

int main() {
    int size;
    printf("Введите размер массива: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Размер массива должен быть положительным.\n");
        return 1;
    }

    int arr[size];

    printf("Введите элементы массива:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    if (hasDuplicates(arr, size)) {
        printf("В массиве есть повторяющиеся элементы.\n");
    } else {
        printf("В массиве нет повторяющихся элементов.\n");
    }

    return 0;
}


№9	В массиве числа образуют неубывающую последовательность. Несколько элементов, идущих подряд, равны между собой. Найти количество таких элементов.
#include <stdio.h>

int main() {
    int size;
    printf("Введите размер массива: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Размер массива должен быть положительным.\n");
        return 1;
    }

    int arr[size];

    printf("Введите элементы массива (неубывающая последовательность):\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    int count = 1; // Начинаем с 1 элемента (первый элемент)
    int duplicates = 0; // Счетчик одинаковых элементов

    for (int i = 0; i < size - 1; i++) {
        if (arr[i] == arr[i + 1]) {
            count++;
        } else {
            if (count > 1) {
                duplicates++;
            }
            count = 1; // Сбрасываем счетчик
        }
    }

    // Проверяем последние элементы
    if (count > 1) {
        duplicates++;
    }

    printf("Количество элементов, равных между собой и идущих подряд: %d\n", duplicates);

    return 0;
}


№10	Изменить знак у максимального по модулю элемента массива.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int size;
    printf("Введите размер массива: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Размер массива должен быть положительным.\n");
        return 1;
    }

    int arr[size];

    printf("Введите элементы массива:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    // Находим максимальный по модулю элемент и его индекс
    int maxAbsValue = abs(arr[0]);
    int maxAbsIndex = 0;

    for (int i = 1; i < size; i++) {
        int absValue = abs(arr[i]);
        if (absValue > maxAbsValue) {
            maxAbsValue = absValue;
            maxAbsIndex = i;
        }
    }

    // Изменяем знак максимального по модулю элемента
    arr[maxAbsIndex] = -arr[maxAbsIndex];

    printf("Массив с измененным знаком у максимального по модулю элемента:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

№11	Даны два массива. Элементы каждого из массивов упорядочены по неубыванию. Объединить элементы этих двух массивов в третий массив так, чтобы они снова оказались упорядоченными по неубыванию.
#include <stdio.h>

void mergeArrays(int arr1[], int size1, int arr2[], int size2, int result[]) {
    int i = 0; // Текущая позиция в первом массиве
    int j = 0; // Текущая позиция во втором массиве
    int k = 0; // Текущая позиция в третьем массиве

    // Продолжаем объединять элементы до тех пор, пока не закончатся оба исходных массива
    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
    }

    // Если первый массив не закончился, добавляем оставшиеся элементы
    while (i < size1) {
        result[k++] = arr1[i++];
    }

    // Если второй массив не закончился, добавляем оставшиеся элементы
    while (j < size2) {
        result[k++] = arr2[j++];
    }
}

int main() {
    int size1, size2;

    printf("Введите размер первого массива: ");
    scanf("%d", &size1);
    int arr1[size1];

    printf("Введите элементы первого массива (упорядоченные по неубыванию):\n");
    for (int i = 0; i < size1; i++) {
        scanf("%d", &arr1[i]);
    }

    printf("Введите размер второго массива: ");
    scanf("%d", &size2);
    int arr2[size2];

    printf("Введите элементы второго массива (упорядоченные по неубыванию):\n");
    for (int i = 0; i < size2; i++) {
        scanf("%d", &arr2[i]);
    }

    int result[size1 + size2]; // Результат объединения массивов
    mergeArrays(arr1, size1, arr2, size2, result);

    printf("Результат объединения массивов (упорядоченный по неубыванию):\n");
    for (int i = 0; i < size1 + size2; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}


№13 Найти сумму элементов массива, расположенных между максимальным и минимальным элементами (включительно).
#include <stdio.h>

int main() {
    int size;
    printf("Введите размер массива: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Размер массива должен быть положительным.\n");
        return 1;
    }

    int arr[size];

    printf("Введите элементы массива:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    // Находим максимальный и минимальный элементы и их индексы
    int maxElement = arr[0];
    int minElement = arr[0];
    int maxIndex = 0;
    int minIndex = 0;

    for (int i = 1; i < size; i++) {
        if (arr[i] > maxElement) {
            maxElement = arr[i];
            maxIndex = i;
        }
        if (arr[i] < minElement) {
            minElement = arr[i];
            minIndex = i;
        }
    }

    // Определяем начальный и конечный индексы для суммирования
    int start = (maxIndex < minIndex) ? maxIndex : minIndex;
    int end = (maxIndex > minIndex) ? maxIndex : minIndex;

    int sum = 0;

    // Суммируем элементы между максимальным и минимальным
    for (int i = start; i <= end; i++) {
        sum += arr[i];
    }

    printf("Сумма элементов между максимальным и минимальным элементами: %d\n", sum);

    return 0;
}


№15	Элементы массива циклически сдвинуть на две позиции влево.
#include <stdio.h>

int main() {
    int size;
    printf("Введите размер массива: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Размер массива должен быть положительным.\n");
        return 1;
    }

    int arr[size];

    printf("Введите элементы массива:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    if (size < 2) {
        printf("Недостаточно элементов для сдвига.\n");
        return 1;
    }

    // Сохраняем первые два элемента во временных переменных
    int temp1 = arr[0];
    int temp2 = arr[1];

    // Перемещаем остальные элементы на две позиции влево
    for (int i = 2; i < size; i++) {
        arr[i - 2] = arr[i];
    }

    // Помещаем временные переменные в конец массива
    arr[size - 2] = temp1;
    arr[size - 1] = temp2;

    printf("Массив после циклического сдвига на две позиции влево:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
