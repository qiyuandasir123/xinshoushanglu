#include <stdio.h>
#include <windows.h>
void sum_line(int a[][3],int n,int *p){
    for (int i=0;i<n;i++){
        (*p)+=a[0][i];
    }
}
int main(){
    int a[3][3]={{1,2,3},{4,5,6},{7,8,9}};
    int sum=0;
    sum_line(a,3,&sum);
    printf("第一行的和是：%d",sum);
    return 0;
}