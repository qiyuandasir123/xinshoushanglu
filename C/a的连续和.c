#include <windows.h>
#include <stdio.h>
int main()
{
    printf("请输入a和n的值：");
    int a, n = 0;
    scanf("%d %d", &a, &n);
    int term = 0;
    int b = 0;
    for (int i = 0; i < n; i++)
    {
        term = term * 10 + a;
        b += term;
    }
    printf("结果为：%d", b);
    return 0;
}