#include <iostream>
#include <thread>
#include <cstdio>
#include <pthread.h>
#include <vector>
#include <string>
#include <signal.h>
#include <unistd.h>
#include <semaphore.h>
#include <algorithm>
#include <list>


// подфункции заданий
//-------
// n1
void printLines() {
    for (int i = 1; i <= 10; ++i) {
        printf("Line %d from thread\n", i);
    }
}
//-------
//n2
void* printLines2(void*) {
    for (int i = 1; i <= 10; ++i) {
        printf("Line %d from thread\n", i);
    }
    return nullptr;
}
//-------
//n3
void* printLine3(void*) {
    for (int i = 1; i <= 10; ++i) {
        printf("Line %d from thread\n", i);
    }
    return nullptr;
}
//-------
//n4
void printLines4(const std::vector<std::string>& lines) {
    for (const std::string& line : lines) {
        std::cout << line << std::endl;
    }
}
//-------
//n5
void* threadFunction(void* arg) {
    int localVariable = 42;
    printf("Thread address: %p, Local variable address: %p\n", (void*)pthread_self(), (void*)&localVariable);
    return NULL;
}
//-------
//n6
static pthread_t childThread;

// функция обработки сигнала SIGINT
void sigintHandler(int signal) {
    std::cout << "Child thread received signal SIGINT with thread ID: " << pthread_self() << std::endl;
}
void* childThreadFunction(void* arg) {
    // перехват сигнала
    signal(SIGINT, sigintHandler);
    while (1) {
        sleep(1);
    }
    return NULL;
}
//-------
//n7
void* childThreadFunction2(void* arg) {
    sleep(2);
    std::cout << "Child thread is running..." << std::endl;
    while (1) {
        sleep(1);
    }
    return NULL;
}

//-------
//n9
static pthread_t childThread3;
// функция для завершения дочерней нити
void cleanupHandler(void* arg) {
    std::cout << "Child thread is cleaning up..." << std::endl;
}

void* childThreadFunction3(void* arg) {
    sleep(2);
    std::cout << "Child thread is running..." << std::endl;
    // очистка при завершении потока
    pthread_cleanup_push(cleanupHandler, NULL);
        while (1) {
            sleep(1);
        }
    pthread_cleanup_pop(1);

    return NULL;
}
//-------
//n10
pthread_mutex_t mutex;
void printLines10() {
    for (int i = 1; i <= 10; ++i) {
        // захват мьютекс перед выводом строки
        pthread_mutex_lock(&mutex);
        printf("Line %d from thread\n", i);
        // освобождаем мьютекс после вывода строки
        pthread_mutex_unlock(&mutex);
    }
}
//-------
//n12
//pthread_mutex_t mutex;
pthread_mutex_t printMutex;
pthread_cond_t condition;
bool childReady = false;
void printLines12() {
    for (int i = 1; i <= 10; ++i) {
        // захват мьютекс для синхронизации вывода
        pthread_mutex_lock(&printMutex);
        // ждем, пока дочерняя нить будет готова к выводу
        while (!childReady) {
            pthread_cond_wait(&condition, &printMutex);
        }
        printf("Line %d from thread\n", i);
        // сигнал для дочерней нити о готовности к выводу
        childReady = false;
        pthread_cond_signal(&condition);
        // освобождаем мьютекс для синхронизации вывода
        pthread_mutex_unlock(&printMutex);
    }
}
//-------
//n13
sem_t readySemaphore;
sem_t printSemaphore;

void printLines13() {
    for (int i = 1; i <= 10; ++i) {
        // Ждем сигнала о готовности
        sem_wait(&readySemaphore);
        // Выводим строку
        printf("Line %d from thread\n", i);
        // Сигнализируем о завершении вывода
        sem_post(&printSemaphore);
    }
}
//-------
//n15
std::list<std::string> stringList;
std::mutex mtx;
void parentThread15() {
    while (true) {
        std::string input;
        std::cout << "Введите строку (или нажмите Enter чтобы вывести отсортированную строку): ";
        std::getline(std::cin, input);

        if (input.empty()) {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "Отсортированный список: " << std::endl;
            for (const std::string& str : stringList) {
                std::cout << str << std::endl;
            }
        } else {
            std::lock_guard<std::mutex> lock(mtx);
            while (input.length() > 80) {
                stringList.push_back(input.substr(0, 80));
                input = input.substr(80);
            }
            stringList.push_back(input);
        }
    }
}
void bubbleSort() {
    while (true) {
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            std::lock_guard<std::mutex> lock(mtx);
            stringList.sort();
        }
    }
}


// Задания
//-------
//n2
void n1() {
    // откл буферизацию stdout
    setvbuf(stdout, NULL, _IONBF, 0);
    // новый поток
    std::thread myThread(printLines);
    // вывод десяти строк
    for (int i = 1; i <= 10; ++i) {
        printf("Нити %d из main\n", i);
    }
    myThread.join();
}
//-------
//n2
void n2() {
    setvbuf(stdout, NULL, _IONBF, 0);
    pthread_t myThread;
    if (pthread_create(&myThread, NULL, printLines2, NULL) != 0) {
        std::cerr << "Не удалось создать поток" << std::endl;
        return;
    }
    // ожидание завершения вторичного потока
    if (pthread_join(myThread, nullptr) != 0) {
        std::cerr << "Не удалось создать поток" << std::endl;
        return;
    }

    // десять строк из главного потока после завершения вторичного потока
    for (int i = 1; i <= 10; ++i) {
        printf("Нить %d из main\n", i);
    }
}
//-------
//n3
void n3() {
    setvbuf(stdout, NULL, _IONBF, 0);
    pthread_t myThread;
    if (pthread_create(&myThread, NULL, printLine3, NULL) != 0) {
        std::cerr << "Не удалось создать поток" << std::endl;
        return;
    }

    // Ждем завершения вторичного потока
    if (pthread_join(myThread, nullptr) != 0) {
        std::cerr << "Не удалось создать поток" << std::endl;
        return;
    }

    // Печатаем десять строк из главного потока после завершения вторичного потока
    for (int i = 1; i <= 10; ++i) {
        printf("Нить %d из main\n", i);
    }
}
//-------
//n4
//void n4() {
//    // Создаем четыре разные последовательности строк
//    std::vector<std::string> lines1 = {"Нить 1 - Строка 1", "Нить 1 - Строка 2", "Нить 1 - Строка 3"};
//    std::vector<std::string> lines2 = {"Нить 2 - Строка 1", "Нить 2 - Строка 2"};
//    std::vector<std::string> lines3 = {"Нить 3 - Строка 1", "Нить 3 - Строка 2", "Нить 3 - Строка 3", "Нить 3 - Строка 4"};
//    std::vector<std::string> lines4 = {"Нить 4 - Строка 1"};
//
//    // Создаем четыре нити и запускаем функцию printLines4 с разными последовательностями строк
//    std::thread thread1(printLines4, lines1);
//    std::thread thread2(printLines4, lines2);
//    std::thread thread3(printLines4, lines3);
//    std::thread thread4(printLines4, lines4);
//
//    // Ждем завершения всех нитей
//    thread1.join();
//    thread2.join();
//    thread3.join();
//    thread4.join();
//}
//-------
//n5
void n5() {
    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, threadFunction, NULL) != 0) {
        std::cerr << "Не удалось создать поток 1" << std::endl;
        return;
    }

    if (pthread_create(&thread2, NULL, threadFunction, NULL) != 0) {
        std::cerr << "Не удалось создать поток 2" << std::endl;
        return;
    }

    if (pthread_join(thread1, NULL) != 0) {
        std::cerr << "Не удалось создать поток 1" << std::endl;
        return;
    }

    if (pthread_join(thread2, NULL) != 0) {
        std::cerr << "Не удалось создать поток 2" << std::endl;
        return;
    }
}
//-------
//n6
void n6() {
    pthread_t thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    // приоритет SCHED_FIFO и уровень 10 (максимальный)
    struct sched_param param;
    param.sched_priority = 10;
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    pthread_attr_setschedparam(&attr, &param);

    // собственный стек для нити
    size_t stackSize = 1024 * 1024; // 1 MB
    void* stack = malloc(stackSize);
    pthread_attr_setstack(&attr, stack, stackSize);
    if (pthread_create(&thread, &attr, threadFunction, NULL) != 0) {
        std::cerr << "Не удалось создать поток" << std::endl;
        return;
    }
    if (pthread_join(thread, NULL) != 0) {
        std::cerr << "Не удалось создать поток" << std::endl;
        return;
    }
    pthread_attr_destroy(&attr);
    free(stack);
}
//-------
//n7
void n7() {
    // дочерня нить
    if (pthread_create(&childThread, NULL, childThreadFunction, NULL) != 0) {
        std::cerr << "Не удалось создать поток" << std::endl;
        return;
    }
    // обработчик сигнала SIGINT
    signal(SIGINT, sigintHandler);
    // сигнал SIGINT из родительской нити в дочернюю
    pthread_kill(childThread, SIGINT);
    // ожидание завершения дочерней нити
    if (pthread_join(childThread, NULL) != 0) {
        std::cerr << "Не удалось подключиться к потоку" << std::endl;
        return;
    }
}
//-------
//n8
void n8() {
    // Создаем дочернюю нить
    if (pthread_create(&childThread, NULL, childThreadFunction, NULL) != 0) {
        std::cerr << "Не удалось создать child потока" << std::endl;
        return;
    }
    sleep(2);
    // прерываем выполнение дочерней нити
    pthread_cancel(childThread);

    // завершения дочерней нити
    if (pthread_join(childThread, NULL) != 0) {
        std::cerr << "Не удалось подключить child потока" << std::endl;
        return;
    }
}
//-------
//n9
void n9() {
    // дочерняя нить
    if (pthread_create(&childThread3, NULL, childThreadFunction3, NULL) != 0) {
        std::cerr << "Не удалось создать child потока" << std::endl;
        return;
    }
    // завершения дочерней нити
    if (pthread_join(childThread3, NULL) != 0) {
        std::cerr << "Не удалось подключить child потока" << std::endl;
        return;
    }
}
//-------
//n10
void n10() {
    setvbuf(stdout, NULL, _IONBF, 0);
    // инициализация
    pthread_mutex_init(&mutex, NULL);

    // новый поток
    std::thread myThread(printLines);
    for (int i = 1; i <= 10; ++i) {
        // захват мьютекс перед выводом строки
        pthread_mutex_lock(&mutex);
        printf("Нить %d из main\n", i);
        // освобождение мьютекс после вывода строки
        pthread_mutex_unlock(&mutex);
    }

    // Ждем завершения вторичного потока
    myThread.join();

    // Уничтожаем мьютекс
    pthread_mutex_destroy(&mutex);
}
//-------
//n12
void n12() {
    // инициализация мьютексы и условную переменную
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&printMutex, NULL);
    pthread_cond_init(&condition, NULL);
    std::thread myThread(printLines12);

    for (int i = 1; i <= 10; ++i) {
        // захват мьютекс для синхронизации между нитями
        pthread_mutex_lock(&mutex);
        // сигнализация для дочерней нити о готовности к выводу
        childReady = true;
        pthread_cond_signal(&condition);
        // ожидаем, пока дочерняя нить завершит вывод строки
        while (childReady) {
            pthread_cond_wait(&condition, &mutex);
        }
        // освобождаем мьютекс для синхронизации между нитями
        pthread_mutex_unlock(&mutex);
    }

    // завершение дочерней нити
    myThread.join();

    // убийсво мьютексы и условную переменную
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&printMutex);
    pthread_cond_destroy(&condition);
}
//-------
//n13
void n13() {
    // инициализация семафоры
    sem_init(&readySemaphore, 0, 0);
    sem_init(&printSemaphore, 0, 0);

    std::thread myThread(printLines13);

    for (int i = 1; i <= 10; ++i) {
        // сигнал о готовности дочерней нити
        sem_post(&readySemaphore);
        // ожидание завершения вывода
        sem_wait(&printSemaphore);
    }

    // ожидание завершения дочерней нити
    myThread.join();

    // убийство семафоры
    sem_destroy(&readySemaphore);
    sem_destroy(&printSemaphore);
}
//-------
//n15
void n15() {
    std::thread parent(parentThread15);
    std::thread child(bubbleSort);

    parent.join();
    child.join();
}


int main() {
    //n1();
    //n2();
    //n3();
    //n4();
    //n5();
    //n6();
    //n7();
    //n8();
    //n9();
    //n10();
    //Задача 10, которая требует синхронизации вывода родительской и дочерней нитей,
    //не может быть решена только с использованием двух мьютексов без использования других
    //средств синхронизации. Это связано с тем, что использование только двух мьютексов не
    //обеспечивает необходимой гарантии чередования вывода строк между нитями.
    //n12();
    //n13();
//    Cемафоры-счетчики не могут быть применены для решения задачи n10,
//    так как они не обеспечивают нужную синхронизацию вывода родительской и дочерней нитей.
//    Семафоры-счетчики позволяют управлять доступом к ресурсам в конкурентной среде, но они
//    не предоставляют средств для координации последовательности выполнения действий между нитями.
    //n15();
    return 0;
}
