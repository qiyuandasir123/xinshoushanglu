#include <stdio.h>
#include <windows.h>
int main()
{
    SetConsoleOutputCP(65001);
    int a = 0;
    int count = 0;
    printf("请输入一个整数：");
    scanf("%d", &a);
    while (a > 0)
    {
        a = a / 10;
        count++;
        printf("a=%d count=%d\n", a, count);
    }
    printf("该整数的位数为：%d\n", count);
    return 0;
}