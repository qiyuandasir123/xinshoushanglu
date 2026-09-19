#include <stdio.h>
#include <windows.h>
int main()
{
    int a[6] = {1, 1, 4, 5, 1, 4};
    int *p = a;
    int found = 0;
    printf("请输入您要搜索的量：");
    int c;
    scanf("%d", &c);
    for (int i = 0; i < 6; i++)
    {
        int x;
        int cha[6] = {0};
        x = (*(p + i) == c);
        cha[i] = x;

        for (int i = 0; i < 6; i++)
        {
            if (cha[i] == 1)
            {
                printf("找到了！在第%d个\n", i);
                found = 1;
            }
        }
    }
    if (found == 0)
    {
        printf("没找到");
    }
    return 0;
}