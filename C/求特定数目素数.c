#include <stdio.h>
#include <windows.h>
int isprime(int i, int prime[], int cnt)
{
    int result = 1;
    for (int j = 0; j < cnt; j++)
    {
        if (i % prime[j] == 0)
        {
            result = 0;
            break;
        }
    }
    return result;
}
int main()
{
    int a, b;
    SetConsoleOutputCP(65001);
    printf("请写出要求素数的区间：");
    scanf("%d %d", &a, &b);
    int prime[100] = {2};
    int cnt = 1;
    for (int i = a; i <= b; i++)
    {
        if (isprime(i, prime, cnt))
        {
            prime[cnt++] = i;
        }
    }
    printf("%d到%d之间的素数有：", a, b);
    for (int i = 0; i < cnt; i++)
    {
        printf("%d ", prime[i]);
    }
    int c;
    printf("\n");
    printf("请输入从零开始要打印的素数个数：");
    scanf("%d", &c);
    int prime2[100] = {2};
    int count = 0;
    while (count <= c)
    {
        for (int e = 2;; e++)
        {
            for (int j = 2; j <= e; j++)
            {
                if (e % j == 0 && e != j)
                {
                    break;
                }
                else if (e == j)
                {
                    printf("%d ", e);
                    prime2[count++] = e;
                }
            }
        }
    }
    printf("\n");
    printf("从零开始的前%d个素数有：", c);
    for (int i = 0; i < count; i++)
    {
        printf("%d ", prime2[i]);
    }
    return 0;
}