#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
int main()
{
    SetConsoleOutputCP(65001);
    srand(time(0));
    int a = rand();
    printf("已生成随机数，请输入你的猜测:");
    int b = 0;
    scanf("%d", &b);
    while (b != a)
    {
        if (b > a)
        {
            printf("太大了，请重新输入");
        }
        else if (b < a)
        {
            printf("太小了，请重新输入");
        }
        scanf("%d", &b);
    }
    printf("恭喜你，猜对了！");
    return 0;
}