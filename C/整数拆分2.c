#include <windows.h>
#include <stdio.h>
#include <math.h>
int main()
{
    int a = 0;
    printf("请输入一个整数(将拆分该数)：");
    scanf("%d", &a);
    int b = 0;
    int t = a;
    while (t > 0)
    {
        t = t / 10;
        ++b;
    }
    printf("该数有%d位\n", b);
    int c = 1;

    while (a > 0 && b > 0)
    {
        c = a / (pow(10, b - 1));
        printf("%d", c);
        a = a - (c * pow(10, b - 1));
        --b;

        printf("\n");
    }
    return 0;
}