#include <windows.h>
#include <stdio.h>
int main()
{
    SetConsoleOutputCP(65001);
    int n = 0;
    int b = 0;
    float a = 0;
    printf("请输入n的值：");
    scanf("%d", &n);
    for (b = 1; b <= n; ++b)
    {
        if (b % 2 == 0)
        {
            a -= 1.0 / b;
        }
        else
        {
            a += 1.0 / b;
        }
    }
    printf("1+1/2+1/3+...+1/n的值为：%f\n", a);
    return 0;
}