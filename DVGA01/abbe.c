#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    srand(time(NULL)); // make rand random
    int o;
    for (int i = 0; i < 901; i++)
    {
        o = 0;
        for (int j = 0; j < 50; j++)
        {

            while (1 == 1)
            {
                o += 1;
                if ((float)rand() * 900 / RAND_MAX == 900)
                {
                    break;
                }
            }
        }
        printf("\n%d - %d", i, o / 5);
    }
}