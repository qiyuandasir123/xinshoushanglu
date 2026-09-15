#include <windows.h>
#include <stdio.h>
int main()
{
    SetConsoleOutputCP(65001);
    int a = 0;
    printf("请输入一个整数(将打印该整数内所有素数)：");
    scanf("%d", &a);
    int b = 2;
    for (b = 2; b < a; b++)
    {
        for (int c = 2; c - 1 < b; c++)
        {
            if (b % c == 0 && b != c)
            {
                break;
            }
            else if (b == c)
            {
                printf("%d ", b);
            }
        }
    }

    return 0;
}