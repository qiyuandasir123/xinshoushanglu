#include <windows.h>
#include <stdio.h>
int main()
{
    SetConsoleOutputCP(65001);
    int a = 0;
    int b = 0;
    printf("请输入金额(角)：");
    scanf("%d", &a);
    b = a / 5;
    int c = (a - b * 5) / 2;
    int d = (a - b * 5 - c * 2);
    printf("5角有：%d个、2角有：%d个、1角有：%d个\n", b, c, d);
    return 0;
}