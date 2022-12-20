#ifndef FIL_H
#define FIL_H

void read_file();
void write_one_vehicle();
void file_exists();
void clear_file();
void write_one_person();
int get_person_age();
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
    char *owner_name;
};

#endif