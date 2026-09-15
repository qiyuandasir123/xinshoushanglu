#include <windows.h>
#include <stdio.h>
int main()
{
    SetConsoleOutputCP(65001);
    printf("请输入两个整数：");
    int a = 0;
    int b = 0;
    scanf("%d %d", &a, &b);
    int min;
    if (a >= b)
    {
        min = b;
    }
    else
    {
        min = a;
    }
    int gcd = 1;
    for (int c = 1; c <= min; ++c)
    {
        if (a % c == 0 && b % c == 0)
        {
            gcd = c;
        }
    }
    printf("最大公约数为：%d\n", gcd);

    return 0;
}