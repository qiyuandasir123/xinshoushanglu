#include <windows.h>
#include <stdio.h>
int main()
{
    SetConsoleOutputCP(65001);
    int i, j, k = 1;
    for (i = 1; i <= 9; i++)
    {
        for (j = 1; j <= 9; j++)
        {
            printf("%d*%d=%d ", i, j, i * j);
        }
        printf("\n");
    }
    return 0;
}