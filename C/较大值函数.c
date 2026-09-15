#include <stdio.h>
#define NOMINMAX
#include <windows.h>
void max(int a, int b)
{
    int ret;
    SetConsoleOutputCP(65001);
    if (a >= b)
    {
        ret = a;
    }
    else
    {
        ret = b;
    }
    printf("%d", ret);
}
int main()
{
    SetConsoleOutputCP(65001);
    int a, b;
    scanf("%d %d", &a, &b);
    max(a, b);
}
