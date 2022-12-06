#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define AMOUNT_NUMBERS 100
#define MAX_SIZE 900
#define WIDTH 10

int print_values(int *values)
{
    for (int i = 0; i < AMOUNT_NUMBERS; i++)
    {
        if (i % WIDTH == WIDTH - 1)
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
    for (int i = 0; i < AMOUNT_NUMBERS; i++)
    {
        values[i] = rand() * (MAX_SIZE + 1) / RAND_MAX;
    }
    print_values(values);
}

int sort(int *values) // bubbelsortering
{
    int temp;
    int sorted = 0;
    while (sorted == 0)
    {
        sorted = 1;
        for (int i = 0; i < AMOUNT_NUMBERS - 1; i++) // - 1 since it checks itself and the next number
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
    int min = MAX_SIZE;

    for (int i = 0; i < AMOUNT_NUMBERS; i++)
    {
        sum += values[i];

        if (values[i] > max)
        {
            max = values[i];
        }

        if (values[i] < min)
        {
            min = values[i];
        }
    }
    float average = sum / (float)AMOUNT_NUMBERS;
    int median = (values[AMOUNT_NUMBERS / 2 - 1] + values[AMOUNT_NUMBERS / 2]) / 2; // / 2 - 1 and / 2 to get the middle numbers

    printf("Min = %d, Max = %d\nAverage = %.2f, Median = %d\n", min, max, average, median);
}

int search(int *values)
{
    int depth = 0;
    int pos = AMOUNT_NUMBERS / 2; // starting search in middle(close)
    printf("Number: ");
    int target;
    scanf("%d", &target);
    int col, jump;
    while (depth < log2(AMOUNT_NUMBERS))
    {
        jump = fmax(ceil(AMOUNT_NUMBERS / pow(2, depth + 2)), 1); // + 2 since jump should start at 1/4 aka 2^2
        if (target == values[pos])
        {
            col = (pos + 1) % WIDTH; // colums starts at 1 while index starts at 0
            if (col == 0)
            {
                col = WIDTH;
            }
            printf("Found %d on col %d row %d\n", target, col, pos / WIDTH + 1); // row starts at 1, index starts at 0
            return 0;
        }
        else if (target > values[pos])
        {
            pos += jump;
            if (pos > 99)
            {
                pos = 99;
            }
        }
        else
        {
            pos -= jump;
            if (pos < 0)
            {
                pos = 0;
            }
        }
        depth += 1;
    }
    printf("Number doesnt exist\n");
    return 0;
}

int main()
{
    srand(time(NULL)); // make rand random

    int state = -1;
    int values[AMOUNT_NUMBERS];
    int input, ch;

    printf("1 Generate values\n2 Sort values\n3 Calculate medium, median, max and minimum number\n4 Search\n0 Quit\n");
    while (1 == 1)
    {
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
        }
        else if (input > 2 && state == 1)
        {
            printf("Must sort values first\n");
        }
        else
        {
            switch (input)
            {
            case 0:
                printf("Program exited");
                return 0;
            case 1:
                generate(values);
                state = 1;
                break;
            case 2:
                sort(values);
                state = 2;
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
}