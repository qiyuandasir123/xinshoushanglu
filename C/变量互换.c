#include <stdio.h>
#include <windows.h>

int main()
{
    SetConsoleOutputCP(65001);
    int a = 0;
    int b = 0;
    printf("请输入两个整数：");
    scanf("%d %d", &a, &b);
    int c = 0;
    c = a;
    a = b;
    b = c;
    printf("%d %d\n", a, b);
    return 0;
}