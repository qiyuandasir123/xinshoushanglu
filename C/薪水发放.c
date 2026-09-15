#include <stdio.h>
#include <windows.h>
int main()
{
    SetConsoleOutputCP(65001);
    const float zi = 50;
    int a = 0;
    printf("请输入工作时长：");
    scanf("%d", &a);
    if (a >= 8)
    {
        printf("您的加班时长为：%d小时、\n", a - 8);
        printf("您的本日工资为：%.2f元、\n", 8 * zi + (a - 8) * zi * 1.5);
    }
    else
    {
        printf("您没有加班、\n");
        printf("您的本日工资为：%.2f元、\n", a * zi);
    }
    return 0;
}