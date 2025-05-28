#ifndef _2_H
#define _2_H

#define MAX_DESTINATION 50
#define MAX_AIRCRAFT 20
#define FILENAME "Spravka.dat"

typedef struct {
    char destination[MAX_DESTINATION];
    int flight_number;
    char aircraft_type[MAX_AIRCRAFT];
} FlightRecord;

void create_file();
void search_flights();
void print_all_flights();

#endif
