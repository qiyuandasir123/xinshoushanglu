#include <stdio.h>
#include <windows.h>
#include <math.h>
int main()
{
    double a, b, c, d, x, f;
    printf("请输入a的值:");
    scanf("%lf", &a);
    printf("请输入b的值:");
    scanf("%lf", &b);
    printf("请输入c的值:");
    scanf("%lf", &c);
    printf("请输入d的值:");
    scanf("%lf", &d);
    printf("请输入x的值:");
    scanf("%lf", &x);
    f = a * pow(x, 3) + b * pow(x, 2) + c * x + d;
    printf("f=%lf\n", f);
    return 0;
}