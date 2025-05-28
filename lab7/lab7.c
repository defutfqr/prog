include <stdio.h>
#include <pthread.h>

void* thread_func(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Дочерний поток: строка %d\n", i + 1);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);

    for (int i = 0; i < 5; i++) {
        printf("Родительский поток: строка %d\n", i + 1);
    }

    pthread_exit(NULL);
}

-------------------------------------

#include <stdio.h>
#include <pthread.h>

void* thread_func(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Дочерний поток: строка %d\n", i + 1);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);
    pthread_join(thread, NULL);  // Ждём завершения потока

    for (int i = 0; i < 5; i++) {
        printf("Родительский поток: строка %d\n", i + 1);
    }

    return 0;
}

-------------------------------------

#include <stdio.h>
#include <pthread.h>

void* thread_func(void* arg) {
    char** messages = (char**)arg;
    for (int i = 0; i < 5; i++) {
        printf("%s\n", messages[i]);
    }
    return NULL;
}

int main() {
    pthread_t threads[4];

    char* msgs1[] = {"one", "two", "three", "four", "five"};
    char* msgs2[] = {"uno", "dos", "tres", "cuatro", "cinco"};
    char* msgs3[] = {"kerran", "kaksi", "kolme", "nelja", "viisi"};
    char* msgs4[] = {"раз", "два", "три", "четыре", "пять"};

    char** msg_sets[] = {msgs1, msgs2, msgs3, msgs4};

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_func, msg_sets[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

-------------------------------------

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_func(void* arg) {
    char** messages = (char**)arg;
    for (int i = 0; i < 5; i++) {
        printf("%s\n", messages[i]);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t threads[4];

    char* msgs1[] = {"one", "two", "three", "four", "five"};
    char* msgs2[] = {"uno", "dos", "tres", "cuatro", "cinco"};
    char* msgs3[] = {"kerran", "kaksi", "kolme", "nelja", "viisi"};
    char* msgs4[] = {"раз", "два", "три", "четыре", "пять"};

    char** msg_sets[] = {msgs1, msgs2, msgs3, msgs4};

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_func, msg_sets[i]);
    }

    sleep(2);  // Подождать 2 секунды

    for (int i = 0; i < 4; i++) {
        pthread_cancel(threads[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

-------------------------------------

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void cleanup(void* arg) {
    printf("Поток завершён принудительно\n");
}

void* thread_func(void* arg) {
    char** messages = (char**)arg;
    pthread_cleanup_push(cleanup, NULL);

    for (int i = 0; i < 5; i++) {
        printf("%s\n", messages[i]);
        sleep(1);
    }

    pthread_cleanup_pop(1);  // Вызов cleanup, если поток прерван
    return NULL;
}

int main() {
    pthread_t threads[4];

    
    char* msgs1[] = {"one", "two", "three", "four", "five"};
    char* msgs2[] = {"uno", "dos", "tres", "cuatro", "cinco"};
    char* msgs3[] = {"kerran", "kaksi", "kolme", "nelja", "viisi"};
    char* msgs4[] = {"раз", "два", "три", "четыре", "пять"};

    char** msg_sets[] = {msgs1, msgs2, msgs3, msgs4};

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_func, msg_sets[i]);
    }

    sleep(2);

    for (int i = 0; i < 4; i++) {
        pthread_cancel(threads[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

-------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 50

void* sleep_sort_func(void* arg) {
    int val = *(int*)arg;
    usleep(val * 1000); // сон в миллисекундах
    printf("%d \n", val);
    free(arg);
    return NULL;
}

int main() {
    int arr[] = {3500, 1000, 5000, 2225, 3999};
    int n = sizeof(arr) / sizeof(arr[0]);

    pthread_t threads[MAX];

    for (int i = 0; i < n; i++) {
        int* val = malloc(sizeof(int));
        *val = arr[i];
        pthread_create(&threads[i], NULL, sleep_sort_func, val);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n");
    
    
    return 0;
}
