#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int m;
    float sum = 0;
    scanf("%d", &m);
    float tal[m];
    for (int i = 0; i < m; i++)
    {
        scanf("%f", &tal[i]);
        sum += tal[i];
    }

    float avg = sum / m;

    float sumsecond;
    for (int i = 0; i < m; i++)
    {
        sumsecond += pow((tal[i] - avg), 2);
    }

    printf("%f", sqrt(sumsecond / (m - 1)));
    return 0;
}
