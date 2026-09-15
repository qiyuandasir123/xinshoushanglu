#include <stdio.h>
#include <windows.h>
int main()
{
    SetConsoleOutputCP(65001);
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    printf("请输入初始时间：");
    scanf("%d%d", &a, &b);
    int m = a * 60 + b;
    printf("请输入终止时间：");
    scanf("%d%d", &c, &d);
    int n = c * 60 + d;
    int cha = n - m;
    int bian = cha % 60;
    int dd = (cha - bian) / 60;
    printf("时间差为：%d小时%d分钟\n", dd, bian);
    return 0;
}