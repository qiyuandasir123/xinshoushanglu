#include <stdio.h>
#include <windows.h>
int main()
{
    SetConsoleOutputCP(65001);
    int a = 0;
    int b = 0;
    printf("输入起始时间：");
    scanf("%d", &a);
    printf("输入终止时间：");
    scanf("%d", &b);
    int ahour = a / 100;
    int bhour = b / 100;
    int aminute = a % 100;
    int bminute = b % 100;
    printf("时间差为：%d小时%d分钟\n", bhour - ahour, bminute - aminute);
    return 0;
}