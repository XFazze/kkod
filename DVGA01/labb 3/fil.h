#ifndef FIL_H
#define FIL_H

struct Vehicle *read_file();
void write_one_vehicle();
void file_exists();
void clear_file();

struct Person
{
    char *name;
    int age;
};

struct Vehicle
{
    char *type;
    char *brand;
    char *reg_num;
    int age;
};

#endif