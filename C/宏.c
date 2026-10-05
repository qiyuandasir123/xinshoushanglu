#include <stdio.h>
#include <windows.h>
#define MAX 114514
#define NEWMAX MAX + 1
#define solonglonglonglonglonglonglonglonglonglonlonglonglonglonglonglonglong\
longlonglonglonglonglonglonglonglong\
long 123456789
int remax(int a, int b){
    return a > b ? a : b;
}
int main (){
    SetConsoleOutputCP(65001);
    printf("%d\n",MAX);
    printf("%d\n",NEWMAX);
    printf("%d\n",solonglonglonglonglonglonglonglonglonglonlonglonglonglonglonglonglong\
longlonglonglonglonglonglonglonglong\
long);
int a,b;
scanf("%d %d",&a,&b);
printf("%d\n",remax(a,b));
    return 0;
}