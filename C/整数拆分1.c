#include <windows.h>
#include <stdio.h>
int main()
{
    int a = 0;
    printf("请输入一个整数(将拆分该数)：");
    scanf("%d", &a);
    int b = 0;
    int t = a;

    while (t > 9)
    {
        b++;
        t = t / 10;
    }
    printf("该数有%d位\n", b + 1);
    int c = 0;
    while (a > 0)
    {
        c = a % 10;
        printf("%d ", c);
        a = a / 10;
    }
    return 0;
}