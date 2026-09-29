#include <stdio.h>
#include <windows.h>
int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    int score;
    printf("请输入成绩：");
    scanf("%d", &score);
    if (score >= 60)
    {
        printf("pass\n");
    }
    else
    {
        printf("fail\n");
    }
    return 0;
}
