#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
int main()
{
    int *a;
    int number;
    printf("请输入元素个数：");
    scanf("%d", &number);
    /*int a[number];*/
    a = malloc(number * sizeof(int));
    for (int i = 0; i < number; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < number; i++)
    {
        printf("%d\n", a[i]);
    }
    free(a);
    return 0;
}