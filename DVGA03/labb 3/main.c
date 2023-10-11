#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "node.h"
#include "driv.h"

int main()
{
    char choices[] = "\
\t0: Avsluta\n\
\t1: Skriv ut listan\n\
\t2: Skriv ut listans storlek\n\
\t3: Lägg till ett heltal sist i listan\n\
\t4: Lägg till ett tal på (valfri plats)\n\
\t5: Ta bort ett givet heltal\n\
\t6: Ta bort ett heltal (valfri plats)\n\
\t7: Töm listan\n\
\t8: Vänd på listan\n\
\t9: Skifta listan ett schoice_bufferteg åt vänster (och lägg första heltalet sist)\n\
\t10: Skifta listan ett steg åt höger (och lägg sista heltalet först)\n\
\t11: Sortera listan (lägsta heltalet först)\n\
\t12: Skriv ut startadress för listan\n\n\
Gör ditt val: \
    ";
    node *head = 0;
    int choice = 1;
    while (choice != 0)
    {
        printf("%s", choices);

        choice = getInput("Choice");
        printf("choice%d\n", choice);

        switch (choice)
        {
        case 0:
            break;
        case 1:
            DPrintList(head);
            break;
        case 2:
            DPrintListSize(head);
            break;
        case 3:
            head = DInsertElement(head);
            break;
        case 4:
            head = DInsertElementAt(head);
            break;
        case 5:
            head = DRemoveInteger(head);
            break;
        case 6:
            head = DRemoveAt(head);
            break;
        case 7:
            head = DClear(head);
            break;
        case 8:
            head = DReverse(head);
            break;
        case 9:
            head = DShiftLeft(head);
            break;
        case 10:
            head = DShiftRight(head);
            break;
        case 11:
            head = DSort(head);
            break;
        case 12:
            DPrintStartAdress(head);
            break;
        }
    }

    return 0;
}