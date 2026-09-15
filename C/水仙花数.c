#include <windows.h>
#include <stdio.h>
#include <math.h>
int main()
{
    SetConsoleOutputCP(65001);
    printf("100~999 内的水仙花数：");
    for (int i = 100; i <= 999; ++i)
    {
        int b = i / 100;
        int c = (i - b * 100) / 10;
        int d = i - b * 100 - c * 10;
        if (i == pow(b, 3) + pow(c, 3) + pow(d, 3))
        {
            printf("%d\n", i);
        }
    }
    printf("\n");
    return 0;
}
