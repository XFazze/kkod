#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "fil.h"
#include "main.h"
// TODO
// Input names are wierd
// input names can be empty
// sort cars
// remove car
// owners
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
    struct Vehicle *vehicles = read_file();
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
}

int int_input()
{
    char buffer[NAME_LENGTH];
    fgets(buffer, NAME_LENGTH, stdin);
    strtok(buffer, "\n");
    while (is_number(buffer) != 1) // not working for letters
    {
        printf("In is numnber");
        fgets(buffer, NAME_LENGTH, stdin);
        strtok(buffer, "\n");
    }
    return atoi(buffer);
}
void add_vehicle()
{
    if (car_amount() == MAX_CARS)
    {
        printf("\nError: Maximum allowed cars(10) already added.");
        return;
    }

    // TODO check empty names

    struct Vehicle new_vehicle;
    printf("\nAdding a vehicle");
    char buffer[NAME_LENGTH];

    printf("\nType: ");
    fgets(buffer, NAME_LENGTH, stdin);
    strtok(buffer, "\n");
    new_vehicle.type = buffer;

    printf("Brand: ");
    fgets(buffer, NAME_LENGTH, stdin);
    strtok(buffer, "\n");
    new_vehicle.brand = buffer;

    printf("Registration number: ");
    fgets(buffer, NAME_LENGTH, stdin);
    strtok(buffer, "\n");
    new_vehicle.reg_num = buffer;

    printf("Age: ");
    new_vehicle.age = int_input();

    printf("\nNew vehicle %s, %s, %s, %d", new_vehicle.type, new_vehicle.brand, new_vehicle.reg_num, new_vehicle.age);

    write_one_vehicle(new_vehicle);
}
void remove_vehicle()
{
    printf("\nRemove vehicle(1-%d): ", car_amount());
    int vehicle_num = int_input();
    if (vehicle_num < 0 || vehicle_num > car_amount())
    {
        printf("Error: vehicle %d doesnt exist", vehicle_num);
    }
    else
    {
        struct Vehicle *vehicles = read_file();
        int new_amount = car_amount() - 1;
        clear_file();
        printf("\n new amount%d", new_amount);
        for (int i = 0; i < new_amount; i++)
        {
            printf("\nvn=%d i=%d:%s", vehicle_num, i, vehicles[i].type);
            if (vehicle_num - 2 < i)
            {
                printf("\nskippiing:%s", vehicles[i].type);
                write_one_vehicle(vehicles[i + 1]);
            }
            else
            {

                write_one_vehicle(vehicles[i]);
            }
        }
    }
}
void sort_vehicles()
{
    printf("sort ASDSA");
}
void info_vehicle()
{
    printf("\nInfo about vehicle(1-%d): ", car_amount());
    int vehicle_num = int_input();
    if (vehicle_num < 0 || vehicle_num > car_amount())
    {
        printf("Error: vehicle %d doesnt exist", vehicle_num);
    }
    else
    {
        struct Vehicle *vehicles = read_file();
        printf("\nVehicle %d: type=%s, brand=%s, reg num=%s, age=%d", vehicle_num, vehicles[vehicle_num - 1].type, vehicles[vehicle_num - 1].brand, vehicles[vehicle_num - 1].reg_num, vehicles[vehicle_num - 1].age);
    }
}
void show_vehicles()
{
    struct Vehicle *vehicles = read_file();
    for (int i = 0; i < MAX_CARS; i++)
    {
        if (vehicles[i].type == NULL)
        {
            break;
        }
        printf("\nVehicle %d: type=%s, brand=%s, reg num=%s, age=%d", i + 1, vehicles[i].type, vehicles[i].brand, vehicles[i].reg_num, vehicles[i].age);
    }
}
int main()
{
    char buffer[MENU_OPTION_LENGTH];
    int option;

    struct Vehicle v = {"aaaa", "aaaa", "aaaa", 1};
    struct Vehicle v2 = {"bbbb", "bbbb", "bbbb", 2};
    struct Vehicle v3 = {"cccc", "cccc", "cccc", 3};
    write_one_vehicle(v);
    write_one_vehicle(v2);
    write_one_vehicle(v3);
    while (1)
    {
        // menu
        printf("\n1. Add vehicle\n2. Remove vehicle\n3. Show vehicles sorted by car brand\n4. Information about a vehicle\n5. Show all vehicles\n0. Exit\n# ");
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