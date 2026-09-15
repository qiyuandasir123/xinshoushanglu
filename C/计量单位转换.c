#include <stdio.h>
#include <windows.h>
int main()
{
    SetConsoleOutputCP(65001);
    float a = 0.0000;
    float b = 0.0000;
    printf("请输入尺寸例5 7表示5尺7寸：");
    scanf("%f %f", &a, &b);
    float m = 0.0000;
    m = (a + b / 12) * 0.3084;
    printf("您的身高为：%.2f米\n", m);
    return 0;
}