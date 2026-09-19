#include <stdio.h>
#include <stdlib.h>
int main() {
    int i=1;
    int const *p=&i;
    printf("*p=%d\n",*p);
    printf("p=%d\n",p);
    *p++;
    printf("*p++=%d\n",*p);
    p++;
    printf("p++=%d\n",p);
    int b=2;
    int const *a=&b;
    printf("*a=%d\n",*a);
    printf("a=%d\n",a);
    *a++;
    b++;
    printf("b++=%d\n",b);
    int c=4;
    int *const q=&c;
    *q=2;
    int d=5;
    const int *r=&d;
    r++;
    printf("*r=%d",*r);

    return 0;
}
