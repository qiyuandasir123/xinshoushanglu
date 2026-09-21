#include <stdio.h>
#include <windows.h>
#include <math.h>
int main()
{
    SetConsoleOutputCP(65001);
    float a, b, c, x1, x2, d;
    printf("请分别输入a,b,c的值（用逗号隔开）");
    if (scanf("%f,%f,%f", &a, &b, &c) != 3)
    { 
        printf("输入格式错误！");
        return 1;
    }
    d = pow(b, 2) - 4 * a * c;
    if (a == 0)
    { 
        printf("错误！a不能为0");
    }
    else if (d < 0)
    {
        printf("错误！");
    }
    else
    {
        d = sqrt(d);
        x1 = (-b + d) / (2 * a);
        x2 = (-b - d) / (2 * a);
        printf("x1=%f,x2=%f", x1, x2);
    }
    return 0;
}