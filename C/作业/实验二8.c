#include <stdio.h>
#include <windows.h>
int main()
{   
    int a;char c;int b;
    scanf("%d %c %d",&a,&c,&b);
    printf("%d %d %c\n",a,b,c);
    printf("%d %d %lld %d %d\n",a+b,a-b,(long long)a*b,a/b,a%b);
    double d=(double)a/b;
    printf("The ratio of %d versus %d is %.2f.\n",a,b,d);
    printf("The ratio of %d / %d is %.2f%%.\n",a,b,d*100);
    return 0;
}