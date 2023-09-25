#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define max(a, b)               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a > _b ? _a : _b;      \
    })

#define MAX_PROCESSES 100
#define MAX_PROCESS_DATA_LENGTH 100
#define MAX_NAME_LENGTH 50

typedef struct Process
{
    int id;
    int arrival_time;
    int burst_time;
} Process;

typedef struct Process_Result
{
    int id;
    int wait_time;
    int turnaround_time;
} Process_Result;

int process_arrival_time_compare(const void *a, const void *b)
{
    Process *process1 = (Process *)a;
    Process *process2 = (Process *)b;
    return (process1->arrival_time - process2->arrival_time);
}

int main(int arc, char **argv)
{
    FILE *fp;
    char *string = NULL;
    char *filename = (char *)calloc(MAX_NAME_LENGTH, sizeof(char));
    char *algorithm = (char *)calloc(MAX_NAME_LENGTH, sizeof(char));
    int quantom_time = 0;
    char file_buffer[MAX_PROCESS_DATA_LENGTH];
    struct Process processes[MAX_PROCESSES];
    int process_count = 0;

    srand(time(NULL));
    for (int i = 0; i < arc; ++i)
    {
        if (strcmp(argv[i], "-f") == 0)
        {
            filename = argv[i + 1];
        }
        if (strcmp(argv[i], "-a") == 0)
        {
            algorithm = argv[i + 1];
        }
        if (strcmp(argv[i], "-q") == 0)
        {
            quantom_time = atoi(argv[i]);
        }
    }
    if (strcmp(filename, "") == 0)
    {
        printf("You need to provide an input file with -f.\n");
        return 0;
    }
    if ((strcmp(algorithm, "fcfs") != 0 && strcmp(algorithm, "sjf") != 0) && strcmp(algorithm, "rr") != 0)
    {
        printf("You need to provide an algorithm with -a.\n");
        return 0;
    }

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Not able to open file");
        fclose(fp);
        return 0;
    }

    while (fgets(file_buffer, MAX_PROCESS_DATA_LENGTH, fp))
    {
        // printf("=%s\n", file_buffer);
        struct Process new_process;
        new_process.id = atoi(strtok(file_buffer, ","));
        new_process.arrival_time = atoi(strtok(NULL, ","));
        new_process.burst_time = atoi(strtok(NULL, ","));
        processes[process_count] = new_process;
        // printf("aaa id:%d arrival:%d burst:%d \n", processes[process_count].id, processes[process_count].arrival_time, processes[process_count].burst_time);
        process_count++;
    }

    int time = 0;
    qsort(processes, process_count, sizeof(Process), process_arrival_time_compare);
    struct Process_Result processes_result[MAX_PROCESSES];

    if (strcmp(algorithm, "fcfs") == 0)
    {
        for (int i = 0; i < process_count; i++)
        {
            Process process = processes[i];
            int wait_time = time - process.arrival_time;
            int turnaround_time = time + process.burst_time - process.arrival_time;
            struct Process_Result new_process = {process.id, wait_time, turnaround_time};
            processes_result[i] = new_process;
            time += processes[i].burst_time;
        }
    }

    else if (strcmp(algorithm, "sjf") == 0)
    {
        bool processes_done[MAX_PROCESSES] = {false};
        int time = 0;
        for (int i = 0; i < process_count; i++)
        {
            int shortest_burst = TMP_MAX;
            int shortest_burst_index = i;
            for (int o = 0; o < process_count; o++)
            {
                Process process = processes[o];
                if (process.arrival_time > time || processes_done[o])
                {
                    continue;
                }
                if (process.burst_time < shortest_burst)
                {
                    // printf("short i:%d id:%d burst: %d shortest burst %d\n", shortest_burst_index, processes[o].id, processes[o].burst_time, shortest_burst);
                    shortest_burst_index = o;
                    shortest_burst = processes[o].burst_time;
                }
            }
            // printf("RESshort i:%d id:%d\n\n", shortest_burst_index, processes[shortest_burst_index].id);
            processes_done[shortest_burst_index] = true;
            Process process = processes[shortest_burst_index];

            struct Process_Result new_process = {process.id, time - process.arrival_time, time + process.burst_time - process.arrival_time};
            processes_result[shortest_burst_index] = new_process;
            time += process.burst_time;
        }
        for (int i = 0; i < process_count; i++)
        {
            Process process = processes[i];
            int wait_time = max(time - process.arrival_time, 0);
            int turnaround_time = max(time + process.burst_time - process.arrival_time, 0);
            // printf("%d %17d %22d\n", process.id, wait_time, turnaround_time);
            time += processes[i].burst_time;
        }
    }

    printf("Process informaion file: %s\n", filename);
    printf("Sorting algorithm: %s\n", algorithm);
    printf("Time quantum: %d ms\n\n", quantom_time);
    printf("PID    Waiting Time(ms)    Turnaround Time(ms)\n");
    int sum_wait_time = 0;
    int sum_turnaround_time = 0;
    for (int i = 0; i < process_count; i++)
    {
        Process_Result process = processes_result[i];
        printf("%d %17d %22d\n", process.id, max(process.wait_time, 0), max(process.turnaround_time, 0));
        sum_wait_time += process.wait_time;
        sum_turnaround_time += process.turnaround_time;
    }
    printf("Average waiting time: %.2f (ms)\n", (float)sum_wait_time / (float)process_count);
    printf("Average turnaround time: %.2f (ms)\n", (float)sum_turnaround_time / (float)process_count);

    fclose(fp);
    return 0;
}