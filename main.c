#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int menu(int state)
{
    while (1 == 1)
    {
        int input, ch;
        printf("# ");
        scanf("%d", &input);
        if (input < -1 || input > 4)
        {
            printf("Error: Input must be 1, 2, 3 or 4\n");
            printf("1 Generate values\n2 Sort values\n3 Calculate medium, median, max and minimum number\n4 Search\n0 Quit\n");
        }
        else if (input > 1 && state == -1)
        {
            printf("Must generate values first\n");
            return -1;
        }
        else if (input > 2 && state == 1)
        {
            printf("Must sort values first\n");
            return -1;
        }
        return input;
    }
}

int print_values(int *values)
{
    for (int i = 0; i < 100; i++)
    {
        if (i % 10 == 9)
        {
            printf("%4d\n", values[i]);
        }
        else
        {
            printf("%4d", values[i]);
        }
    }
}

int generate(int *values)
{
    int r;
    for (int i = 0; i < 100; i++)
    {
        r = rand() * 900 / RAND_MAX;
        values[i] = r;
    }
    print_values(values);
}

int sort(int *values)
{
    int temp;
    int sorted = 0;
    while (sorted == 0)
    {
        sorted = 1;
        for (int i = 0; i < 99; i++)
        {
            if (values[i] > values[i + 1])
            {
                sorted = 0;
                temp = values[i];
                values[i] = values[i + 1];
                values[i + 1] = temp;
            }
        }
    }
    printf("Values sorted\n");
    print_values(values);
}

int avgs(int *values)
{
    int sum = 0;
    int max = 0;
    int min = 900;

    for (int i = 0; i < 100; i++)
    {
        sum = +values[i];

        if (values[i] > max)
        {
            max = values[i];
        }

        if (values[i] < min)
        {
            min = values[i];
        }
    }
    float average = sum / 100.0;
    int median = (values[49] + values[50]) / 2;

    printf("Min = %d, Max = %d\nAverage = %.2f, Median = %d\n", min, max, average, median);
}

int search(int *values)
{
    int depth = 1;
    int pos = 50; // Starting in middle
    printf("Number: ");
    int target;
    scanf("%d", &target);
    int col, jump;
    while (1 == 1)
    {
        jump = fmax(50 / pow(2, depth), 1);
        if (depth > 8)
        {
            break;
        }
        else if (target == values[pos])
        {
            col = (pos + 1) % 10;
            if (col == 0)
            {
                col = 10;
            }
            printf("Found %d on col %d row %d\n", target, col, pos / 10 + 1);
            return 0;
        }
        else if (target > values[pos])
        {
            pos += jump;
        }
        else
        {
            pos -= jump;
        }
        depth += 1;
        printf("depth %d, pos %d, jump %d, rn %d\n", depth, pos, jump, values[pos]);
    }
    printf("Number doesnt exist\n");
}

int main()
{
    srand(time(NULL)); // make rand random

    int menu_option = -1;
    int values[100]; // 100 will always be the length of the array

    printf("1 Generate values\n2 Sort values\n3 Calculate medium, median, max and minimum number\n4 Search\n0 Quit\n");
    while (1 == 1)
    {
        menu_option = menu(menu_option);
        switch (menu_option)
        {
        case 0:
            printf("Program exited");
            return 0;
        case 1:
            generate(values);
            break;
        case 2:
            sort(values);
            break;

        case 3:
            avgs(values);
            break;
        case 4:
            search(values);
            break;
        }
    }
}