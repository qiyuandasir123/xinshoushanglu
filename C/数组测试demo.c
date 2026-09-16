#include <stdio.h>

int main(void)
{
    int a[5] = {10, 20, 30, 40, 50};
    int i;

    for (i = 0; i < 5; i++) {
        printf("a[%d]=%2d   *(a+%d)=%2d   地址=%p\n",
               i, a[i], i, *(a + i), (void *)&a[i]);
    }
    printf("2[a] = %d\n", 2[a]);          /* 冷知识 */
    printf("元素个数 = %d\n", (int)(sizeof(a) / sizeof(a[0])));

    return 0;
}