#include <stdio.h>
#include <windows.h>
int main()
{
    SetConsoleOutputCP(65001);
    printf("请输入两个整数：");
    int b = 0;
    int a = 0;
    scanf("%d %d", &a, &b);
    printf("%d+%d=%d\n", a, b, a + b);
    printf("%d-%d=%d\n", a, b, a - b);
    printf("%d*%d=%d\n", a, b, a * b);
    printf("%d/%d=%f\n", a, b, (float)(a) / (float)(b));
    return 0;
}