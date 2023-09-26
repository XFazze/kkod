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
    char address[6];
    int page;
} Logical_memory;

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
    int pages[MAX_LOGICAL_MEMORY_ADRESSES];
    int page_count = 0;
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
        struct Logical_memory new_logical_memory;
        memcpy(new_logical_memory.address, file_buffer + 2, 4);
        // printf("page %s\n", file_buffer);
        char page[20];
        memcpy(page, file_buffer + 3, 1);
        // printf("pageb %s\n", page);

        new_logical_memory.page = atoi(page);
        logical_memory[memory_count] = new_logical_memory;
        printf("aaa address:%s page:%d  \n", logical_memory[memory_count].address, logical_memory[memory_count].page);
        memory_count++;
    }
    fclose(fp);

    if (strcpy(algorithm, "fifo") == 0)
    {
        int order[MAX_LOGICAL_MEMORY_ADRESSES];
        int order_max_index = 0;
        int order_queue_index = 0;

        while (1)
        {
            for (int i = 0; i < memory_count; i++)
            {
                if (pages[logical_memory[i].page])
                {
                    printf("Address %s is on page %d which is already in physical memory\n", logical_memory[i].address, logical_memory[i].page);
                }
                else
                {
                    printf("Address");
                    if (page_count < frames_number)
                    {
                        page_count++;
                        pages[logical_memory[i].page] = 1;
                        order[order_max_index] = logical_memory[i].page;
                        order_max_index++;
                    }
                    else
                    {
                        printf("Page #%d is paged out", order[order_queue_index]);
                        printf("Page #%d is paged in", logical_memory[i].page);
                        order[order_queue_index] = logical_memory[i].page;
                        order_queue_index++;
                        if (order_queue_index >= page_count)
                        {
                            order_queue_index = 0;
                        }
                    }
                }
            }
        }
    }

    return 0;
}
