#include <stdio.h>
int main()
{
    int a[5] = {0};
    int *p;
    p = a;
    printf("*(p+1)=%d", *(p + 1));
    return 0;
}