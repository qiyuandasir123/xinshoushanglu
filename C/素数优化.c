#include <windows.h>
#include <stdio.h>
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
    SetConsoleOutputCP(65001);
    int prime[100] = {2};
    int cnt = 1;
    int a = 3;
    for (a = 3; a <= 100; a++)
    {
        if (isprime(a, prime, cnt))
        {
            prime[cnt++] = a;
        }
        printf("a=%d cnt=%d %d\n", a, cnt, prime[cnt - 1]);
    }
    printf("100以内的素数有：");
    for (int i = 0; i < cnt; i++)
    {
        printf("%d ", prime[i]);
    }
    return 0;
}