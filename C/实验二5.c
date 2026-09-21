#include <stdio.h>
#include <windows.h>
int main()
{
    printf("请输入三个整数，用空格隔开");
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    printf("%8d %8d %8d ",a,b,c);
    return 0;
}