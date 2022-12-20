#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fil.h"
#include "main.h"

void read_file(struct Vehicle *vehicles)
{
    file_exists("vehicles.dat");
    FILE *f = fopen("vehicles.dat", "r");
    if (!f)
    {
        printf("Error opening vehicle file");
        exit(1);
    }

    struct Vehicle vehicle;
    int i = 0;
    while (fread(&vehicle, sizeof(struct Vehicle), 1, f))
    {
        // printf("\nREAD new  vehicle %s, %s, %s, %d", vehicle.type, vehicle.brand, vehicle.reg_num, vehicle.age);
        vehicles[i] = vehicle;
        i++;
    }
    fclose(f);
}
void write_one_vehicle(struct Vehicle vehicle)
{
    file_exists("vehicles.dat");

    FILE *f = fopen("vehicles.dat", "a");
    if (!f)
    {
        printf("Error opening vehicle file");
        exit(1);
    }

    // printf("\nWritting new  vehicle %s, %s, %s, %d", vehicle.type, vehicle.brand, vehicle.reg_num, vehicle.age);
    fwrite(&vehicle, sizeof(struct Vehicle), 1, f);
    fclose(f);
}
void file_exists(char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (!f)

    {
        printf("\ncreated file");
        f = fopen(file_name, "w");
    }
    fclose(f);
}
void clear_file()
{
    FILE *f = fopen("vehicles.dat", "w");
    if (!f)
    {
        printf("Error opening vehicle file at clear file");
        exit(1);
    }
    fclose(f);
}

void write_one_person(struct Person person)
{
    file_exists("persons.dat");

    FILE *f = fopen("persons.dat", "a");
    if (!f)
    {
        printf("Error opening vehicle file");
        exit(1);
    }

    // printf("\nWritting new  vehicle %s, %s, %s, %d", vehicle.type, vehicle.brand, vehicle.reg_num, vehicle.age);
    fwrite(&person, sizeof(struct Person), 1, f);
    fclose(f);
}

int get_person_age(char *name)
{
    file_exists("persons.dat");
    FILE *f = fopen("persons.dat", "r");
    if (!f)
    {
        printf("Error opening vehicle file");
        exit(1);
    }
    int age;
    struct Person temp_person;
    while (fread(&temp_person, sizeof(struct Person), 1, f))
    {
        if (strcmp(temp_person.name, name) == 0)
        {
            age = temp_person.age;
        }
    }
    fclose(f);
    return age;
}