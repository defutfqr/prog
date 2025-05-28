#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "2.h"

void create_file() {
    FILE *file = fopen(FILENAME, "wb");
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

    int count = sizeof(records) / sizeof(FlightRecord);
    if (fwrite(records, sizeof(FlightRecord), count, file) != count) {
        printf("Ошибка записи в файл\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
    printf("Файл успешно создан с %d записями.\n", count);
}

void search_flights() {
    FILE *file = fopen(FILENAME, "rb");
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
