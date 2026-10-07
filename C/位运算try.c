#line 2 "D:\\code\\C\\位运算try.c"
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
int main(void)
{
    SetConsoleOutputCP(65001);
    unsigned char a=0xAA;
    //printf("~a=%hhx\n",~a);
    //printf("-a=%hhx\n",-a);
    unsigned char b=0x23;
    printf("a&b=%hhx\n",a&b);
    printf("a|b=%hhx\n",a|b);
    printf("a^b=%hhx\n",a^b);
    printf("~a=%hhx\n",~a);
    printf("a<<2=%hhx\n",a<<2);
    printf("a>>2=%hhx\n",a>>2);
    int c=0x80000000;
    printf("c=%hhx\n",c);
    printf("c=%d\n",c);
    printf("c>>2=%hhx\n",c>>2);
    printf("c>>2=%d\n",c>>2);
    return 0;
}