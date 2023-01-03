#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fil.h"
#include "main.h"

int read_file(struct Vehicle *vehicles)
{
    file_exists("vehicles.txt");
    FILE *f = fopen("vehicles.txt", "r");
    if (!f)
    {
        printf("Error opening vehicle file");
        exit(1);
    }

    int i=0;
    while(fscanf(f,"%s %s %s %d %s\n", vehicles[i].type, vehicles[i].brand,vehicles[i].reg_num, &vehicles[i].age, vehicles[i].owner_name)!=EOF){
        i++;
    }
    fclose(f);
    return i;
}
void write_one_vehicle(struct Vehicle vehicle)
{
    file_exists("vehicles.txt");

    FILE *f = fopen("vehicles.txt", "a");
    if (!f)
    {
        printf("Error opening vehicle file");
        exit(1);
    }

     printf("\nWritting new  vehicle %s, %s, %s, %d", vehicle.type, vehicle.brand, vehicle.reg_num, vehicle.age);
    fprintf(f,"%s %s %s %d %s\n", vehicle.type, vehicle.brand, vehicle.reg_num, vehicle.age, vehicle.owner_name );
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
    FILE *f = fopen("vehicles.txt", "w");
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