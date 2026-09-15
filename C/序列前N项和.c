#include <windows.h>
#include <stdio.h>
int main()
{
    int n;
    printf("请输入一个整数：");
    scanf("%d", &n);
    float b = 0.00;
    for (int i = 1; i <= n; i++)
    {
        b += (i + 1.0) / i;
    }
    printf("2/1+3/2+……+（n+1）/n=%f", b);
    return 0;
}
