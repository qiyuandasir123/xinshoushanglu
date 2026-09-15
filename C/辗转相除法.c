#include <windows.h>
#include <stdio.h>
int main()
{
    printf("请输入两个整数：");
    int a = 1;
    int b = 1;
    int c = 1;
    scanf("%d %d", &a, &b);
    while (b != 0)
    {
        c = a % b;
        a = b;
        b = c;
    }
    printf("最大公因数为：%d", a);
    return 0;
}