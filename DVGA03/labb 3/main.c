#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "node.h"
#include "driv.h"



int main() {
    char menu_choices[] = "\
        \t0: Avsluta\n\
        \t1: Skriv ut listan\n\
        \t2: Skriv ut listans storlek\n\
        \t3: Lägg till ett heltal sist i listan\n\
        \t4: Lägg till ett tal på (valfri plats)\n\
        \t5: Ta bort ett givet heltal\n\
        \t7: Ta bort ett heltal (valfri plats)\n\
        \t7: Töm listan\n\
        \t8: Vänd på listan\n\
        \t9: Skifta listan ett steg åt vänster (och lägg första heltalet sist)\n\
        \t10: Skifta listan ett steg åt höger (och lägg sista heltalet först)\n\
        \t11: Sortera listan (lägsta heltalet först)\n\
        \t12: Skriv ut startadress för listan\n\n\
        Gör ditt val: \
    ";

    while (1) {
        printf("%s", menu_choices);

        char choice_buffer[2];
        int choice;

        fgets(choice_buffer, 2, stdin);
        strtok(choice_buffer, "\n");
        choice = atoi(choice_buffer);
        printf("%d\n", choice);
    }


    return 0;
}