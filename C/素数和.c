#include <windows.h>
#include <stdio.h>
int main()
{
    SetConsoleOutputCP(65001);
    printf("请输入两个整数：");
    int a, b = 0;
    int d = 0;
    scanf("%d %d", &a, &b);
    for (int i = a; i <= b; i++)
    {
        int is_prime = i > 1;
        for (int u = 2; u < i; u++)
        {
            if (i % u == 0)
            {
                is_prime = 0;
                break;
            }
        }
        if (is_prime)
            d += i;
    }
    printf("从%d到%d间的素数和是：%d", a, b, d);
    return 0;
}