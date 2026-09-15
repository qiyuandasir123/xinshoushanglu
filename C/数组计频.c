#include <windows.h>
#include <stdio.h>
int main()
{
    SetConsoleOutputCP(65001);
    int a;
    int count[10];
    for (int i = 0; i < 10; i++)
    {
        count[i] = 0;
    }
    scanf("%d", &a);
    while (a != -1)
    {
        if (a >= 0 && a <= 9)
        {
            count[a]++;
            scanf("%d", &a);
        }
        else
        {
            printf("输入错误，请重新输入：");
            scanf("%d", &a);
        }
    }
    for (int i = 0; i < 10; i++)
    {
        printf("%d:%d\n", i, count[i]);
    }
    return 0;
}
