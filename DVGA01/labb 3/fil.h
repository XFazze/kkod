#ifndef FIL_H
#define FIL_H

void read_file();
void write_one_vehicle();

struct person
{
    char *name;
    int age;
};

struct vehicle
{
    char *type;
    char *brand;
    char *reg_num;
    int age;
};

#endif