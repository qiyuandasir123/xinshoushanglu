#include <stdio.h>
#include <windows.h>
void interchange(int *m,int *n);
int main(void){
    int m,n;
    printf("请输入m,n的值:");
    scanf("%d %d",&m,&n);
    printf("m的初始值为：%d，n的初始值为：%d\n",m,n);
    interchange(&m,&n);
    printf("m的初始值为：%d，n的现在值为：%d\n",m,n);
    return 0;
}
void interchange(int *m,int *n){
    int i;
    i=*n;
    *n=*m;
    *m=i;
}