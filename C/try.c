#include <stdio.h>
#include <windows.h>
int sum(int a, int b)
{
    int cnt = 0;
    int i;
    for (i = a; i <= b; i++)
    {
        cnt += i;
    }
    return cnt;
}
int main()
{
    SetConsoleOutputCP(65001);
    int a, b;
    scanf("%d %d", &a, &b);
    int result = sum(a, b);
    printf("%d", result);
}
