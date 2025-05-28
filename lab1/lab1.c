#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define N 100
#define NAME_LENGTH 64

struct Student {
    char name[NAME_LENGTH];
    int math;
    int phy;
    int inf;
    int total;
};

struct Student addStudent(const char* name, int math, int phy, int inf) {
    struct Student newStudent;
    strncpy(newStudent.name, name, NAME_LENGTH - 1);
    newStudent.name[NAME_LENGTH - 1] = '\0';
    newStudent.math = math;
    newStudent.phy = phy;
    newStudent.inf = inf;
    newStudent.total = math + phy + inf;
    return newStudent;
}

void printStudentInfo(struct Student student) {
    printf("Name: %s, Math: %d, Physics: %d, Informatics: %d, Total: %d\n",
           student.name, student.math, student.phy, student.inf, student.total);
}

void insertionSort(struct Student arr[], int size) {
    for (int i = 1; i < size; i++) {
        struct Student key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].total < key.total) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    srand(time(NULL));
    struct Student students[N];
    const char* names[] = {"Alice", "Bob", "Charlie", "David", "Eve", "Frank", "Grace", "Hank", "Ivy", "Jack"};

    for (int i = 0; i < N; i++) {
        int nameIndex = rand() % 10;
        int math = rand() % 101;
        int phy = rand() % 101;
        int inf = rand() % 101;
        students[i] = addStudent(names[nameIndex], math, phy, inf);
    }

    printf("Before sorting:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
    }

    insertionSort(students, N);

    printf("\nAfter sorting:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
    }

    return 0;
}
