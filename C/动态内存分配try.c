#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    SetConsoleOutputCP(65001);
    int *p = malloc(12 * sizeof(int));
    if (p == NULL)
    {
        printf("内存分配失败");
        return 0;
    }
    for (int i = 0; i < 10; i++)
    {
        p[i] = i;
    }
    for (int i = 0; i < 12; i++)
    {
        printf("%d ", p[i]);
    }
    
    int *a = realloc(p, 30 * sizeof(int));
    if (!a)
    {
        printf("内存申请失败\n");
        free(p); /* 失败时原内存还在，不能漏掉 */
        return 0;
    }
    for (int i = 0; i < 12; i++)
    {
        a[i] = 60 + i;
    }
    for (int i = 0; i < 30; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    free(a);
    a = NULL;
    /* 释放后置空，防止野指针*/
    /*还有个calloc函数，可以分配内存并初始化为0，这里先不写了*/
    return 0;
}