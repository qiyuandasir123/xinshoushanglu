#include <windows.h>
#include <stdio.h>
#define NUM 1111111
int main()
{
    SetConsoleOutputCP(65001);
    int prime[NUM] = {2};
    int cnt = 1;
    int number[NUM] = {0};
    for (int i = 0; i < NUM; i++)
    {
        number[i] = i;
    }
    for (int b = 2; b < NUM; b++)
    {
        for (int a = 2; a < NUM; a++)
        {
            if (number[a] % b == 0 && number[a] != b)
            {
                number[a] = 0;
            }
            else if (number[a] == b)
            {
                prime[cnt++] = number[a];
            }
        }
    }
    for (int i = 0; i < cnt; i++)
    {
        printf("%d ", prime[i]);
    }
    return 0;
}