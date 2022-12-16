#include <stdio.h>
#include <stdlib.h>

#include "fil.h"
#include "main.h"

void add_vehicle()
{
    printf("add ASDSA");
    read_file();
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