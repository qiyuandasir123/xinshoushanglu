#include <stdio.h>
#include <windows.h>
int main()
{
    char a;
    printf("请输入字符：");
    scanf("%c",&a);
    printf("  %c\n",a);
    printf(" %c%c%c\n",a,a,a);
    printf("%c%c%c%c%c\n",a,a,a,a,a);
    printf(" %c%c%c\n",a,a,a);
    printf("  %c",a);
    return 0;
}