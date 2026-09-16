#include <stdio.h>
#include <windows.h>
int main(){
    int a[]={1,2,3,4,5};
    int *pa1=&a;
    int *pa2=&a[1];
    int *pa3=&a[2];
    printf("pa1=%d\npa2=%d\npa3=%d\n", *pa1, *pa2, *pa3);
    printf("pa1=%p\npa2=%p\npa3=%p\n", pa1, pa2, pa3);
    return 0;
}