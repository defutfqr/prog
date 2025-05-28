#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_DESTINATION 50
#define MAX_AIRCRAFT 20
#define FILENAME "Spravka.dat"

typedef struct { //структура данных о рейсе
    char destination[MAX_DESTINATION];
    int flight_number;
    char aircraft_type[MAX_AIRCRAFT];
} FlightRecord;

void create_file() { //создание файла
    FILE *file = fopen(FILENAME, "wb"); //write + bin
    if (file == NULL) { 
        printf("Ошибка создания файла\n");
        exit(EXIT_FAILURE);
    }

    FlightRecord records[] = {
        {"Москва", 101, "Boeing 737"},
        {"Санкт-Петербург", 202, "Airbus A320"},
        {"Новосибирск", 303, "Boeing 777"},
        {"Сочи", 404, "Airbus A321"},
        {"Владивосток", 505, "Boeing 747"}
    };

    int count = sizeof(records) / sizeof(FlightRecord); //колво рейсов
    if (fwrite(records, sizeof(FlightRecord), count, file) != count) {
        printf("Ошибка записи в файл\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
    printf("Файл успешно создан с %d записями.\n", count);
}

void search_flights() { //ищем рейс
    FILE *file = fopen(FILENAME, "rb"); //read+bin
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        exit(EXIT_FAILURE);
    }

    char search_destination[MAX_DESTINATION];
    printf("Введите пункт назначения для поиска: ");
    fgets(search_destination, MAX_DESTINATION, stdin);
    search_destination[strcspn(search_destination, "\n")] = '\0';

    FlightRecord record;
    int found = 0;

    printf("\nРезультаты поиска:\n");
    while (fread(&record, sizeof(FlightRecord), 1, file) == 1) {
        if (strcmp(record.destination, search_destination) == 0) {
            printf("Пункт: %s, Рейс: %d, Самолет: %s\n",
                  record.destination, record.flight_number, record.aircraft_type);
            found = 1;
        }
    }

    if (!found) {
        printf("Рейсов в пункт '%s' не найдено.\n", search_destination);
    }

    fclose(file);
}

void print_all_flights() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Файл не найден. Сначала создайте файл.\n");
        return;
    }

    FlightRecord record;
    printf("\nВсе рейсы:\n");
    while (fread(&record, sizeof(FlightRecord), 1, file) == 1) {
        printf("Пункт: %s, Рейс: %d, Самолет: %s\n",
              record.destination, record.flight_number, record.aircraft_type);
    }
    fclose(file);
}

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
