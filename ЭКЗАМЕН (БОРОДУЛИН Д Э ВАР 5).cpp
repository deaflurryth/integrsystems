//
// Created by deaflurryth ¿ on 10.01.2024.
//
// БОРОДУЛИН Д Э ПМ20-5, Билет 5

#include <iostream>
#include <vector>

using namespace std;
// ЗАДАНИЕ 2
// функция для сдвига влево на два
void leftRotateByTwo(int arr[], int n) {
    if (n > 1) {
        int temp1 = arr[0], temp2 = arr[1];
        for (int i = 0; i < n - 2; i++) {
            arr[i] = arr[i + 2];
        }
        arr[n - 2] = temp1;
        arr[n - 1] = temp2;
    }
}
// ЗАДАНИЕ 3
// функция для нахождения суммы элементов между минимальным и максимальным
int sumBetweenMinAndMax(int arr[], int n) {
    if (n == 0) return 0;

    int minIndex = 0, maxIndex = 0, sum = 0;

    // нахождение индексов минимального и максимального элементов
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[minIndex]) minIndex = i;
        if (arr[i] > arr[maxIndex]) maxIndex = i;
    }
    if (minIndex > maxIndex) swap(minIndex, maxIndex);

    // вычисление суммы
    for (int i = minIndex; i <= maxIndex; i++) {
        sum += arr[i];
    }

    return sum;
}
int main() {
    cout << "Второе задание" << endl;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Исходный массив: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    leftRotateByTwo(arr, n);

    cout << "Массив после сдвига влево на два: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Третье задание" << endl;
    cout << "В качестве массива был использован из предыдущего задания" << endl;
    int sum = sumBetweenMinAndMax(arr, n);
    cout << "Сумма элементов между минимальным и максимальным: " << sum << endl;
    return 0;
}
