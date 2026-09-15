#include <windows.h>
#include <stdio.h>
int main()
{
    SetConsoleOutputCP(65001);
    printf("请输入分数：");
    int a, b, min, c, d = 1;
    int i = 2;
    scanf("%d %d", &a, &b);
    if (b == 0)
    {
        c = 0;
    }
    else
    {
        c = 1;
    }
    switch (c)
    {
    case 0:
        printf("分母不能为 0\n");
        break;
    case 1:
        if (a < b)
            min = a;
        else
            min = b;
        for (i = min; i >= 2; i--)
        {
            if (a % i == 0 && b % i == 0)
            {
                d = i;
                break;
            }
        }
        int e = a / d;
        int f = b / d;
        printf("化简完后等于：%d/%d", e, f);
        return 0;
    }
}