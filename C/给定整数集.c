#include <windows.h>
#include <stdio.h>
int main()
{
    printf("请输入整数：");
    int a = 1;
    int b;
    int c;
    int d;
    scanf("%d", &a);
    for (b = a; b <= a + 3; ++b)
    {
        for (c = a; c <= a + 3; ++c)
        {
            for (d = a; d <= a + 3; ++d)
            {
                if (b != c)
                {
                    if (c != d)
                    {
                        printf("%d%d%d\n", b, c, d);
                    }
                }
            }
        }
    }

    return 0;
}