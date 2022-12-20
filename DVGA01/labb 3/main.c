#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "fil.h"
#include "main.h"
// TODO
// Input names are wierd
// input names can be empty
// error when not deleting save file

int is_number(char *string)
{
    for (int i = 0; i < strlen(string) - 1; i++)
    {
        if (isdigit(string[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}

int car_amount()
{
    int amount = 0;
    struct Vehicle *vehicles = malloc(sizeof(struct Vehicle) * MAX_CARS);
    memset(vehicles, 0, sizeof(struct Vehicle) * MAX_CARS);
    read_file(vehicles);
    for (int i = 0; i < MAX_CARS; i++)
    {
        if (vehicles[i].type == NULL)
        {
            break;
        }
        else
        {
            amount += 1;
        }
    }
    return amount;
    free(vehicles);
}

void int_input(char *buffer)
{
    fgets(buffer, NAME_LENGTH, stdin);
    strtok(buffer, "\n");
    while (is_number(buffer) != 1) // not working for letters
    {
        printf("Error: not a number. Enter a number:");
        fgets(buffer, NAME_LENGTH, stdin);
        strtok(buffer, "\n");
    }
}

void add_vehicle()
{
    if (car_amount() == MAX_CARS)
    {
        printf("\nError: Maximum allowed cars(10) already added.");
        return;
    }

    struct Vehicle new_vehicle;
    printf("\nAdding a vehicle.");

    char typeb[NAME_LENGTH];
    printf("\nType: ");
    fgets(typeb, NAME_LENGTH, stdin);
    strtok(typeb, "\n");
    new_vehicle.type = typeb;

    char brandb[NAME_LENGTH];
    printf("Brand: ");
    fgets(brandb, NAME_LENGTH, stdin);
    strtok(brandb, "\n");
    // int blen = strlen(brandb);
    // brandb[blen - 3] = 0;
    new_vehicle.brand = brandb;

    char regb[NAME_LENGTH];
    printf("Registration number: ");
    fgets(regb, NAME_LENGTH, stdin);
    strtok(regb, "\n");
    new_vehicle.reg_num = regb;

    char ab[NAME_LENGTH];
    printf("Age: ");
    int_input(ab);
    new_vehicle.age = atoi(ab);

    struct Person person;
    char owner_nameb[NAME_LENGTH];
    printf("Owner name: ");
    fgets(owner_nameb, NAME_LENGTH, stdin);
    strtok(owner_nameb, "\n");
    person.name = owner_nameb;
    new_vehicle.owner_name = owner_nameb;

    char owner_ageb[NAME_LENGTH];
    printf("Owner age: ");
    int_input(owner_ageb);
    person.age = atoi(owner_ageb);

    printf("\nNew vehicle   %s, %s, %s, %d %s", new_vehicle.type, new_vehicle.brand, new_vehicle.reg_num, new_vehicle.age, new_vehicle.owner_name);
    struct Vehicle v = {new_vehicle.type, new_vehicle.brand, new_vehicle.reg_num, new_vehicle.age + 1, new_vehicle.owner_name};
    struct Person p = {"aaa", 123};
    write_one_vehicle(v);
    write_one_person(p);
    char *a = "ff";
    struct Vehicle vf = {a, "ffff", "ffff", 3, "aaa"};
    if (a == "ff\0")
    {
        printf("\n\end of line");
    }
    else if (a == "ff")
    {

        printf("\n\n no end of line");
    }
    write_one_vehicle(vf);
    write_one_person(person);
    write_one_vehicle(new_vehicle);
}

void remove_vehicle()
{
    printf("\nRemove vehicle(1-%d): ", car_amount());
    char buffer[NAME_LENGTH];
    int_input(buffer);
    int vehicle_num = atoi(buffer);
    if (vehicle_num < 0 || vehicle_num > car_amount())
    {
        printf("Error: vehicle %d doesnt exist", vehicle_num);
    }
    else
    {
        struct Vehicle *vehicles = malloc(sizeof(struct Vehicle) * MAX_CARS);
        memset(vehicles, 0, sizeof(struct Vehicle) * MAX_CARS);
        read_file(vehicles);
        int new_amount = car_amount() - 1;
        clear_file();
        for (int i = 0; i < new_amount; i++)
        {
            if (vehicle_num - 2 < i)
            {
                write_one_vehicle(vehicles[i + 1]);
            }
            else
            {
                write_one_vehicle(vehicles[i]);
            }
        }
        free(vehicles);
    }
}

void sort_vehicles()
{
    struct Vehicle *vehicles = malloc(sizeof(struct Vehicle) * MAX_CARS);
    memset(vehicles, 0, sizeof(struct Vehicle) * MAX_CARS);
    read_file(vehicles);
    clear_file();
    int best_choice = 0;
    int taken[MAX_CARS];
    while (1)
    {
        for (int i = 0; i < MAX_CARS; i++)
        {
            if (vehicles[i].brand == NULL)
            {
                continue;
            }
            else if (strcmp(vehicles[i].brand, vehicles[best_choice].brand) < 0)
            {
                best_choice = i;
            }
        }
        write_one_vehicle(vehicles[best_choice]);
        vehicles[best_choice].brand = NULL;
        best_choice = -1;
        for (int o = 0; o < MAX_CARS; o++)
        {
            if (vehicles[o].brand != NULL)
            {
                best_choice = o;
            }
        }
        if (best_choice == -1)
        {
            break;
        }
    }
    free(vehicles);
}

void info_vehicle()
{
    printf("\nInfo about vehicle(1-%d): ", car_amount());
    char buffer[NAME_LENGTH];
    int_input(buffer);
    int vehicle_num = atoi(buffer);
    if (vehicle_num < 0 || vehicle_num > car_amount())
    {
        printf("\nError: vehicle %d doesnt exist", vehicle_num);
    }
    else
    {
        struct Vehicle *vehicles = malloc(sizeof(struct Vehicle) * MAX_CARS);
        memset(vehicles, 0, sizeof(struct Vehicle) * MAX_CARS);
        read_file(vehicles);
        struct Person person;
        int age = get_person_age(vehicles[vehicle_num - 1].owner_name);
        printf("Vehicle %d\nType:%s \nBrand:%s \nReg num:%s \nAge:%d \nOwner:%s \nOwner age:%d",
               vehicle_num, vehicles[vehicle_num - 1].type, vehicles[vehicle_num - 1].brand, vehicles[vehicle_num - 1].reg_num, vehicles[vehicle_num - 1].age, vehicles[vehicle_num - 1].owner_name, age);
        free(vehicles);
    }
}

void show_vehicles()
{
    struct Vehicle *vehicles = malloc(sizeof(struct Vehicle) * MAX_CARS);
    memset(vehicles, 0, sizeof(struct Vehicle) * MAX_CARS);
    read_file(vehicles);
    printf(" # %15s %15s %15s %5s", "type", "brand", "reg", "age");
    for (int i = 0; i < MAX_CARS; i++)
    {
        if (vehicles[i].type == NULL)
        {
            break;
        }
        printf("\n%2d %15s %15s %15s %3d", i + 1, vehicles[i].type, vehicles[i].brand, vehicles[i].reg_num, vehicles[i].age);
    }
    free(vehicles);
}

int main()
{
    char buffer[MENU_OPTION_LENGTH];
    int option;

    struct Vehicle v = {"aaa", "abaa", "aaa", 1, "aaa"};
    struct Vehicle v2 = {"bbbb", "abbbb", "bbbb", 2, "aaa"};
    struct Vehicle v3 = {"cccc", "acccc", "cccc", 3, "aaa"};
    struct Person p = {"aaa", 3};
    write_one_person(p);
    write_one_vehicle(v2);
    write_one_vehicle(v);
    write_one_vehicle(v3);
    while (1)
    {
        // menu
        printf("\n\n1. Add vehicle\n2. Remove vehicle\n3. Show vehicles sorted by car brand\n4. Information about a vehicle\n5. Show all vehicles\n0. Exit\n# ");
        fgets(buffer, MENU_OPTION_LENGTH - 1, stdin);
        option = atoi(buffer);
        if (option == MENU_OPTION_1)
        {
            add_vehicle();
        }
        else if (option == MENU_OPTION_2)
        {
            remove_vehicle();
        }
        else if (option == MENU_OPTION_3)
        {
            sort_vehicles();
        }
        else if (option == MENU_OPTION_4)
        {
            info_vehicle();
        }
        else if (option == MENU_OPTION_5)
        {
            show_vehicles();
        }
        else if (option == MENU_OPTION_6)
        {
            exit(0);
        }
        else
        {
            printf("\nError: option doesnt exist");
        }
    }
}