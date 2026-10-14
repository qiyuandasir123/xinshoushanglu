#include <stdio.h>
#include <windows.h>
int main()
{
    SetConsoleOutputCP(65001);
    float a;
    printf("请输入一个浮点数：");
    scanf("%f",&a);
    int n = a >= 0 ? (int)(a + 0.5) : (int)(a - 0.5);  
    printf("%d", n);
    return 0;
}