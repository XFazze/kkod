#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main()
{
    int max;
    scanf("%d", &max);
    int input[max];

    for (int i = 0; i < max; i++)
    {
        scanf("%d", &input[i]);
    }
    for (int i = 0; i < max; i++)
    {
        if (i == 0)
        {
            printf("%4d", input[i]);
        }
        else if (i % 5 == 0)
        {
            printf("\n%4d", input[i]);
        }
        else
        {

            printf("%4d", input[i]);
        }
    }
}