#ifndef FIL_H
#define FIL_H
#define NAME_LENGTH 32

int read_file();
void write_one_vehicle();
void file_exists();
void clear_file();
void write_one_person();
int get_person_age();
struct Person
{
    char name[NAME_LENGTH];
    int age;
};

struct Vehicle
{
    char type[NAME_LENGTH];
    char brand[NAME_LENGTH];
    char reg_num[NAME_LENGTH];
    int age;
    char owner_name[NAME_LENGTH];
};

#endif