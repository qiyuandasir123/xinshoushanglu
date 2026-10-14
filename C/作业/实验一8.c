#include <stdio.h>
#include <windows.h>
int main()
{
    double ben = 10000;
    int cnt = 0;
    while (cnt < 3)
    {
        ben *= 0.9;
        cnt++;
    }
    printf("3年后资产为：%lf\n", ben);

    return 0;
}