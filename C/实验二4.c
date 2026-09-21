#include <stdio.h>
#include <windows.h>
#include <math.h>
int main()
{
    SetConsoleOutputCP(65001);
    float a;
    printf("请输入一个浮点数：");
    scanf("%f",&a);
    int n = (int)round(a);   
    printf("%d", n);
    return 0;
}