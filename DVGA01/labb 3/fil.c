#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fil.h"
#include "main.h"

struct Vehicle *read_file()
{
    file_exists();
    FILE *f = fopen("vehicles.dat", "r");
    struct Vehicle *vehicles = malloc(sizeof(struct Vehicle) * MAX_CARS);
    struct Vehicle vehicle;
    int i = 0;
    while (fread(&vehicle, sizeof(struct Vehicle), 1, f))
    {
        // printf("\nREAD new  vehicle %s, %s, %s, %d", vehicle.type, vehicle.brand, vehicle.reg_num, vehicle.age);
        vehicles[i] = vehicle;
        i++;
    }
    fclose(f);
    return vehicles;
}
void write_one_vehicle(struct Vehicle vehicle)
{
    file_exists();

    FILE *f = fopen("vehicles.dat", "a");

    fwrite(&vehicle, sizeof(struct Vehicle), 1, f);
    // printf("\nWritting new  vehicle %s, %s, %s, %d", vehicle.type, vehicle.brand, vehicle.reg_num, vehicle.age);
    fclose(f);
}
void file_exists()
{
    FILE *f;
    f = fopen("vehicles.dat", "r");
    if (f == NULL)
    {
        printf("\ncreated file");
        f = fopen("vehicles.dat", "w");
    }
    fclose(f);
}
void clear_file()
{
    fclose(fopen("vehicles.dat", "w"));
}