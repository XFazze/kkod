#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#include "analyze.h"
#include "algorithm.h"
#include "ui.h"
#include "io.h"

//
// Private
//

void get_delta_time(struct timespec start, struct timespec finish, struct timespec *delta)
{
    long int nsec = finish.tv_nsec - start.tv_nsec + delta->tv_nsec;
    long int sec = finish.tv_sec - start.tv_sec + delta->tv_sec;
    if (nsec < 0)
    {
        sec--;
        nsec = pow(10, 9) + nsec;
    }
    if (nsec > pow(10, 9))
    {
        nsec -= pow(10, 9);
        sec++;
    }
    delta->tv_nsec = nsec;
    delta->tv_sec = sec;
}

void get_array(const algorithm_t algorithm, const case_t case_, int *arr, int n)
{
    if (algorithm == binary_search_t)
    {
        for (int i = 0; i < n; i++)
            arr[i] = i;

        return;
    }
    switch (case_)
    {
    case best_t:
        for (int i = 0; i < n; i++)
            arr[i] = i;
        break;
        if (algorithm == binary_search_t)
        {
            arr[n / 2] = n;
        }
    case worst_t:
        if (algorithm == quick_sort_t)
        {
            for (int i = 0; i < n; i++)
            {
                arr[i] = (i < n / 2) ? n / 2 - i : n - i + n / 2;
                // first half contains lower descending numbers
                // second half higher descending number tex 321654
            }
        }
        else
        {
            for (int i = 0; i < n; i++)
                arr[i] = SIZE_START * pow(2, ITERATIONS) - i;
        }
        break;

    case average_t:
        for (int i = 0; i < n; i++)
            arr[i] = (random() % RAND_MAX);

        break;
    default:
        break;
    }
    return;
}

void time_algoritm(result_t *buf, int *arr, void sort_function(), bool search_function(), const algorithm_t algorithm, const case_t case_, int result_length, int target)
{

    for (int iteration = 0; iteration < result_length; iteration++)
    {
        int size = pow(2, iteration) * SIZE_START;
        struct timespec start, finish, delta;
        delta.tv_nsec = 0;
        delta.tv_sec = 0;
        for (int i = 0; i < ITERATIONS; i++)
        {
            get_array(algorithm, case_, arr, size);

            if (algorithm == binary_search_t && case_ == best_t)
                target = size / 2;

            (target != -1) ? search_function(arr, size, target) : sort_function(arr, size);
        }
        for (int i = 0; i < ITERATIONS; i++)
        {
            get_array(algorithm, case_, arr, size);
            if (algorithm == binary_search_t)
                quick_sort(arr, size);

            if (algorithm == binary_search_t && case_ == best_t)
                target = size / 2;

            clock_gettime(CLOCK_MONOTONIC, &start);
            (target != -1) ? search_function(arr, size, target) : sort_function(arr, size);
            clock_gettime(CLOCK_MONOTONIC, &finish);
            get_delta_time(start, finish, &delta);
        }
        buf[iteration] = (result_t){size, (float)delta.tv_sec / ITERATIONS + (float)delta.tv_nsec / (ITERATIONS * pow(10, 9))};
    }
}
//
// Public
//
void benchmark(const algorithm_t algorithm, const case_t case_, result_t *buf, int result_length)
{
    int max_size = pow(2, result_length) * SIZE_START;
    int arr[max_size];
    switch (algorithm)
    {
    case bubble_sort_t:
        time_algoritm(buf, arr, bubble_sort, linear_search, algorithm, case_, result_length, -1);
        break;

    case insertion_sort_t:
        time_algoritm(buf, arr, insertion_sort, linear_search, algorithm, case_, result_length, -1);
        break;

    case quick_sort_t:
        time_algoritm(buf, arr, quick_sort, linear_search, algorithm, case_, result_length, -1);
        break;

    case linear_search_t:
        time_algoritm(buf, arr, bubble_sort, linear_search, algorithm, case_, result_length, 0); // sus worst
        break;

    case binary_search_t:
        time_algoritm(buf, arr, bubble_sort, binary_search, algorithm, case_, result_length, SIZE_START * ITERATIONS); // not best/worst/average
        break;

    default:
        break;
    }
}
