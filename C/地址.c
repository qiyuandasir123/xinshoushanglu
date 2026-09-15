#include <stdio.h>
#include <windows.h>
void f(int *p)
{
    printf("i的地址是:0x%p\n", p);
}
int main()
{
    int i = 1;
    printf("i的地址是:0x%p\n", &i);
    f(&i);
    return 0;
}