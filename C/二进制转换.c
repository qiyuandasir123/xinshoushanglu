#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
int main(void)
{
    SetConsoleOutputCP(65001);
    int a=0xAA;
    printf("a=%hhx\n",a);
    printf("a=%d\n",a);
    printf("a=%o\n",a);
    printf("a=%u\n",a);
    printf("请输入一个整数：");
    int number;
    scanf("%d", &number);
    unsigned changer=1u<<31;
    for (;changer;changer=changer>>1){
        if(number&changer){
            printf("1");
        }else{
            printf("0");
        }
    }
    return 0;
}