#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "fil.h"
#include "main.h"

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
void add_vehicle()
{
    // TODO add check for full register
    struct vehicle new_vehicle;
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

    printf("\nRegistration number: ");
    fgets(buffer, NAME_LENGTH, stdin);
    strtok(buffer, "\n");
    new_vehicle.reg_num = buffer;

    printf("Age: ");
    fgets(buffer, NAME_LENGTH, stdin);
    strtok(buffer, "\n");
    while (!is_number(buffer))
    {
        fgets(buffer, NAME_LENGTH, stdin);
    }
    new_vehicle.age = atoi(buffer);

    printf("\nNew vehicle %s, %s, %s, %d", new_vehicle.type, new_vehicle.brand, new_vehicle.reg_num, new_vehicle.age);

    write_one_vehicle(new_vehicle);
}
void remove_vehicle()
{
    printf("remove ASDSA");
    write_file();
}
void sort_vehicles()
{
    printf("sort ASDSA");
}
void info_vehicle()
{
    printf("info ASDSA");
}
void show_vehicles()
{
    printf("show ASDSA");
}
int main()
{
    char buffer[MENU_OPTION_LENGTH];
    int option;
    while (1)
    {
        // menu
        printf("\n1. Add vehicle\n2. Remove vehicle\n3. Show vehicles sorted by car brand\n4. Information about a vehicle\n5. Show all vehicles\n# ");
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
        else
        {
            printf("\nError: option doesnt exist");
        }
    }
}