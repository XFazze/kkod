#include <stdio.h>
#include <string.h>
#include <ctype.h>
int is_number(char *string)
{
    for (int i = 0; i < strlen(string) - 1; i++)
    {
        printf("\n(%c)== %d", string[i], isdigit(string[i]));
        if (isdigit(string[i]) == 0)
        {
            return 0;
        }
    }
    printf("return 1");
    return 1;
}
int main()
{
    char a = 'a';
    printf("\naaaa%d", isdigit(a));
    char b = '1';
    printf("\naaaa%d", isdigit(b));

    char o[] = "12";
    printf("\nasd%d", is_number(o));
}