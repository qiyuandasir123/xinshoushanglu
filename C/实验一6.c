#include <stdio.h>
#include <windows.h>
#define PI 3.1415926
int main()
{
    double r = 2, h = 5;
    double v = (PI * r * r * h) / 3;
    printf("圆柱体的体积是：%lf\n", v);
    return 0;
}