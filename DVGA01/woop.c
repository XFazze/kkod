#include <stdio.h>
#include <math.h>
int main()
{
    int input;
    scanf("%d", &input);
    int ans;
    ans = floor(log2(input)) + 2;
    if (input == 1)
    {
        ans = 1;
    }
    else if (input == 2)
    {
        ans = 2;
    }
    printf("%d", ans);
    return 0;
}
// 1 : 1
// 2 : 2
// 3-4 : 3
// 5-8 : 4
// 9-16 : 5
// 17-32 : 6

// 2 4 8 16 32