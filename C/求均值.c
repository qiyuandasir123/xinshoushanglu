#include <stdio.h>
#include <windows.h>
int main()
{
    SetConsoleOutputCP(65001);
    float a = 0.0000;
    float sum = 0.0000;
    int count = 0;
    printf("请输入若干个数，输入0结束：");
    do
    {
        scanf("%f", &a);
        sum += a;
        count++;
    } while (a != 0);
    float jun = sum / (count - 1);
    printf("平均值为：%.2f\n", jun);
    return 0;
}