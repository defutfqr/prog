#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char destination[50];
    int train_number;
    int departure_time[2];
} Train;

void create_train_file(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Error creating file");
        return;
    }

    Train trains[] = {
        {"Moscow", 101, {8, 30}},
        {"St.Petersburg", 202, {12, 45}},
        {"Kazan", 303, {6, 15}},
        {"Novosibirsk", 404, {23, 0}},
        {"Ekatirenburg", 505, {14, 20}},
    };

    size_t count = sizeof(trains) / sizeof(trains[0]);

    for (size_t i = 0; i < count; i++) {
        fwrite(&trains[i], sizeof(Train), 1, file);
    }

    fclose(file);
    printf("File '%s' successfully created with %zu logs.\n", filename, count);
}


int compare_time(int t1[2], int t2[2]) {
    return (t1[0] == t2[0]) && (t1[1] == t2[1]);
}

void search_trains(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int search_by_all;
    printf("Find on all fields? (1 - yes, 0 - no): ");
    scanf("%d", &search_by_all);

    Train key = { "", 0, {0, 0} };
    int search_dest = 0, search_num = 0, search_time = 0;

    if (search_by_all || (!search_by_all && printf("Find on destination? (1 - yes, 0 - no): ") && scanf("%d", &search_dest) && search_dest)) {
        printf("Enter destination: ");
        scanf(" %[^\n]", key.destination);  // Пропускаем пробелы
    }
    if (search_by_all || (!search_by_all && printf("Find on train number? (1 - yes, 0 - no): ") && scanf("%d", &search_num) && search_num)) {
        printf("Enter train number: ");
        scanf("%d", &key.train_number);
    }
    if (search_by_all || (!search_by_all && printf("Find on departure time? (1 - yes, 0 - no): ") && scanf("%d", &search_time) && search_time)) {
        printf("Enter departure time (hours, minutes): ");
        scanf("%d %d", &key.departure_time[0], &key.departure_time[1]);
    }

    Train current;
    int found = 0;

    while (fread(&current, sizeof(Train), 1, file) == 1) {
        int match = 1;

        if ((search_dest || search_by_all) && strcmp(current.destination, key.destination) != 0)
            match = 0;
        if ((search_num || search_by_all) && current.train_number != key.train_number)
            match = 0;
        if ((search_time || search_by_all) && !compare_time(current.departure_time, key.departure_time))
            match = 0;

        if (match) {
            found = 1;
            printf("\nFound train:\n");
            printf("Destination: %s\n", current.destination);
            printf("Train number: %d\n", current.train_number);
            printf("Departure time: %02d:%02d\n", current.departure_time[0], current.departure_time[1]);
        }
    }

    if (!found) {
        printf("Information not found.\n");
    }

    fclose(file);
}

int main() {
    create_train_file("train.dat");
    search_trains("train.dat");
    return 0;
}
