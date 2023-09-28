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
#define MAX_PROCESS_DATA_LENGTH 100
#define MAX_LOGICAL_MEMORY_ADRESSES 100
#define MAX_NAME_LENGTH 100

typedef struct Logical_memory
{
    char address[4];
    int page;
} Logical_memory;
void lru_access_order(int *access_order, int access_index, int order_max_index, int reused)
{
    int passed_reused_value = 0;
    // printf("lru accers called max:%d\n", order_max_index);
    for (int i = order_max_index; i > 0; i--)
    {
        if (reused == 0 || passed_reused_value)
        {
            access_order[i] = access_order[i - 1];
        }
        else if (access_order[i - 1] == access_index)
        {

            passed_reused_value = 1;
        }
    }
    access_order[0] = access_index;
    // for (int i = 0; i < order_max_index; i++)
    // {
    //     printf("%d ", access_order[i]);
    // }
    // printf("\n");

    // printf("moved %d to %d # %d to %d\n", access_order[i - 1], access_order[i], i - 1, i);
}
int optimal_find_unique(int *order, int *used_next, int frames_number)
{
    int least_used_page = 0;
    for (int i = 0; i < frames_number; i++)
    {
        int found_unique = 1;
        for (int o = 0; o < frames_number; o++)
        {
            if (order[i] == used_next[o])
            {
                found_unique = 0;
            }
        }
        if (found_unique)
        {
            // printf("Found not used value = %d\n", order[i]);
            return order[i];
        }
    }
    // printf("Found last used value = %d\n", used_next[frames_number]);
    return used_next[frames_number];
}
void optimal_find_next_used(int frames_number, int start_index, int *used_next, Logical_memory *logical_memory)
{
    int used_next_index = 0;
    for (int i = start_index + 1; i < frames_number; i++)
    {
        int used_next_duplicate = 0;
        for (int o = 0; o < frames_number; o++)
        {
            if (used_next[o] == logical_memory[i].page)
            {
                used_next_duplicate = 1;
            }
        }

        if (used_next_duplicate == 0)
        {
            used_next[used_next_index] = logical_memory[i].page;
        }
        if (used_next_index == frames_number)
        {
            break;
        }
    }
}

int main(int arc, char **argv)
{
    FILE *fp;
    char *string = NULL;
    char *filename = (char *)calloc(MAX_NAME_LENGTH, sizeof(char));
    char *algorithm = (char *)calloc(MAX_NAME_LENGTH, sizeof(char));
    int frames_number = 0;
    char file_buffer[MAX_PROCESS_DATA_LENGTH];
    struct Logical_memory logical_memory[MAX_LOGICAL_MEMORY_ADRESSES];
    int memory_count = 0;
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
        if (strcmp(argv[i], "-n") == 0)
        {
            frames_number = atoi(argv[i + 1]);
        }
    }
    if (strcmp(filename, "") == 0)
    {
        printf("You need to provide an input file with -f.\n");
        return 0;
    }
    if ((strcmp(algorithm, "fifo") != 0 && strcmp(algorithm, "optimal") != 0) && strcmp(algorithm, "lru") != 0)
    {
        printf("You need to provide an algorithm with -a.\n");
        return 0;
    }
    if (frames_number == 0)
    {
        printf("You need to provide frame number with -n.\n");
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
        // printf("file buffer %s\n", file_buffer);
        struct Logical_memory new_logical_memory;
        strncpy(new_logical_memory.address, file_buffer + 2, 4);
        // printf("address %s\n", new_logical_memory.address);

        new_logical_memory.page = file_buffer[3] - 48;
        logical_memory[memory_count] = new_logical_memory;
        // printf("aaa address:%s page:%d  \n", logical_memory[memory_count].address, logical_memory[memory_count].page);
        memory_count++;
    }
    fclose(fp);

    int pages[MAX_LOGICAL_MEMORY_ADRESSES] = {0};
    int page_count = 0;
    int memory_accesses = 0;
    int page_hits = 0;
    int page_faults = 0;
    int page_replacements = 0;

    if (strcmp(algorithm, "fifo") == 0)
    {
        int order[MAX_LOGICAL_MEMORY_ADRESSES];
        int order_max_index = 0;
        int order_queue_index = 0;

        for (int i = 0; i < memory_count; i++)
        {
            // printf("loop %d pages  \n", i);
            printf("\n");
            memory_accesses++;
            if (pages[logical_memory[i].page])
            {
                printf("Address %s is on page %d which is already in physical memory\n", logical_memory[i].address, logical_memory[i].page);
                page_hits++;
            }
            else
            {
                printf("Address %s not in physical memory\n", logical_memory[i].address);
                if (page_count < frames_number)
                {
                    page_count++;
                    pages[logical_memory[i].page] = 1;
                    order[order_max_index] = logical_memory[i].page;
                    order_max_index++;
                    printf("Page #%d is paged in\n", logical_memory[i].page);
                }
                else
                {
                    printf("Page #%d is paged out\n", order[order_queue_index]);
                    pages[order[order_queue_index]] = 0;
                    printf("Page #%d is paged in\n", logical_memory[i].page);
                    pages[logical_memory[i].page] = 1;
                    order[order_queue_index] = logical_memory[i].page;
                    order_queue_index++;
                    if (order_queue_index >= page_count)
                    {
                        order_queue_index = 0;
                    }
                    page_replacements++;
                }
                page_faults++;
            }
        }
    }
    else if (strcmp(algorithm, "lru") == 0)
    {
        int access_order[MAX_LOGICAL_MEMORY_ADRESSES] = {0};
        int order_max_index = 0;

        for (int i = 0; i < memory_count; i++)
        {
            // printf("loop %d pages  \n", i);
            printf("\n");
            memory_accesses++;
            if (pages[logical_memory[i].page])
            {
                printf("Address %s is on page %d which is already in physical memory\n", logical_memory[i].address, logical_memory[i].page);
                lru_access_order(access_order, logical_memory[i].page, order_max_index, 1);
                page_hits++;
            }
            else
            {
                printf("Address %s not in physical memory\n", logical_memory[i].address);
                if (page_count < frames_number)
                {
                    page_count++;
                    pages[logical_memory[i].page] = 1;
                    lru_access_order(access_order, logical_memory[i].page, order_max_index, 0);

                    order_max_index++;
                    printf("Page #%d is paged in\n", logical_memory[i].page);
                }
                else
                {
                    printf("Page #%d is paged out\n", access_order[page_count - 1]);
                    pages[access_order[page_count]] = 0;
                    printf("Page #%d is paged in\n", logical_memory[i].page);
                    pages[logical_memory[i].page] = 1;
                    lru_access_order(access_order, logical_memory[i].page, order_max_index, 0);

                    page_replacements++;
                }
                page_faults++;
            }
        }
    }
    else if (strcmp(algorithm, "optimal") == 0)
    {
        int order[MAX_LOGICAL_MEMORY_ADRESSES];
        int order_max_index = 0;
        int used_next[frames_number];
        int order_queue_index = 0;

        for (int i = 0; i < memory_count; i++)
        {
            // printf("loop %d pages  \n", i);
            printf("\n");
            memory_accesses++;
            if (pages[logical_memory[i].page])
            {
                printf("Address %s is on page %d which is already in physical memory\n", logical_memory[i].address, logical_memory[i].page);
                page_hits++;
            }
            else
            {
                printf("Address %s not in physical memory\n", logical_memory[i].address);
                if (page_count < frames_number)
                {
                    page_count++;
                    pages[logical_memory[i].page] = 1;

                    order[order_max_index] = logical_memory[i].page;
                    order_max_index++;

                    order_max_index++;
                    printf("Page #%d is paged in\n", logical_memory[i].page);
                }
                else
                {
                    memset(used_next, 0, frames_number * sizeof(int));
                    optimal_find_next_used(frames_number, i, used_next, logical_memory);
                    int replace_page = optimal_find_unique(order, used_next, frames_number);

                    printf("Page #%d is paged out\n", replace_page);
                    pages[replace_page] = 0;
                    printf("Page #%d is paged in\n", logical_memory[i].page);
                    pages[logical_memory[i].page] = 1;
                    for (int o = 0; o < frames_number; o++)
                    {
                        if (replace_page == order[o])
                        {
                            // printf("reaplcae in orddr %d with %d", order[o], logical_memory[i].page);
                            order[o] = logical_memory[i].page;
                            break;
                        }
                    }

                    page_replacements++;
                }
                page_faults++;
            }
        }
    }
    printf("\nRunning simulation...Done.\n\nSimulation Summary\n\n");
    printf("%-20s %s\n", "Algorithm:", algorithm);
    printf("%-20s %d\n", "Frames:", frames_number);
    printf("%-20s %d\n", "Memeory accesses:", memory_accesses);
    printf("%-20s %d\n", "Page hits:", page_hits);
    printf("%-20s %d\n", "Page faults:", page_faults);
    printf("%-20s %d\n", "Page replacements:", page_replacements);

    return 0;
}