#include <stdio.h>
#include <windows.h>
int main()
{   
    int a;char c;int b;
    scanf("%d %c %d",&a,&c,&b);
    printf("%d %d %d\n",a,b,c);
    printf("%d %d %d\n",a+b,a-b,a*b,a/b,a%b);
    float d=(float)a/b;
    printf("The ratio of %d versus %d is %f\n",a,b,d);
    d*=100;
    printf("The ratio of %d / %d is %.2f %%\n",a,b,d);
    return 0;
}