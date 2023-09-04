// Online C compiler to run C program online
#include <stdio.h>

main() {
    int a,b,c; // объявление переменных
    printf("Введите два целых числа\n");//подскахка для ввода
    scanf("%d%d", &a, &b); //ввод данных
    c = a + b; // вычисление
    printf("Результат %d + %d = %d \n",a,b,c);
}