//
// Created by deaflurryth ¿ on 25.11.2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    //ЗАДАНИЕ 1
    FILE *file = fopen("/Users/deaflurryth/Documents/программирование встроенных систем/integrsystems/Домашние задания/log.txt", "r");
    if (file == NULL) {
        perror("Не удается открыть файл");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
    //ЗАДАНИЕ 2
    int exit_code = 200;
    while (fgets(line, sizeof(line), file)) {
        int code;
        if (sscanf(line, "%*s %*s %*s [%*s] %*s %d\n", &code) == 1) {
            printf("Считанная строка: %s\n", line);
            if (code == exit_code) {
                printf("Найдено совпадение: %s", line);
            }
        }
    }

    fclose(file);
    return 0;
}
