#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "2.h"

int main() {
    // Настройка локали и кодировки
    setlocale(LC_ALL, "ru_RU.UTF-8");
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    int choice;
    
    do {
        printf("\nМеню:\n");
        printf("1. Создать файл с записями\n");
        printf("2. Поиск рейсов по пункту назначения\n");
        printf("3. Показать все рейсы\n");
        printf("4. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                create_file();
                break;
            case 2:
                search_flights();
                break;
            case 3:
                print_all_flights();
                break;
            case 4:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 4);

    return 0;
}
