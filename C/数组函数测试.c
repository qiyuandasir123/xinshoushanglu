#include <stdio.h>
#include <windows.h>

int sum(int *p, int len); /* 函数原型：必须写在调用之前 */

int main()
{
    SetConsoleOutputCP(65001);
    int a, b;
    scanf("%d %d", &a, &b);
    int buf[8] = {0};
    int *p = buf;

    buf[0] = a;
    buf[1] = b;
    int result = sum(p, sizeof(buf) / sizeof(buf[0]));
    printf("%d", result);
    return 0;
}
int sum(int *p, int len)
{
    int res = 0;                  /* 累加器声明在循环外面 */
    for (int i = 0; i < len; i++) /* i 必须初始化 */
    {
        res += p[i];
    }
    return res; /* return 放在循环外面 */
}