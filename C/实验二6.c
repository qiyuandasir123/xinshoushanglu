#include <stdio.h>
#include <windows.h>
int main()
{
    printf("请输入华氏度：");
    float F;
    scanf("%f",&F);
    float C=5*(F-32)/9;
    printf("%.5f",C);
    return 0;
}