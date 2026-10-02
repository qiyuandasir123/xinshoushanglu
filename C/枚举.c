#include <stdio.h>
#include <windows.h>
enum { RED, GREEN, BLUE };
int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    int color;
    enum color { RED, GREEN, BLUE };
    scanf("%d", &color);
    switch (color)
    {
        case RED:
        printf("红色\n");
        break;
        case GREEN:
        printf("绿色\n");
        break;
        case BLUE:
        printf("蓝色\n");
        break;
        default:
        printf("未知颜色\n");
        break;

    }
    return 0;
}