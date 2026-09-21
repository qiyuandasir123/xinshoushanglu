#include <stdio.h>
#include <windows.h>
#include <math.h>
int main(){
    float r;const float PI=3.1415926;
    printf("请输入半径：");
    scanf("%f",&r);
    float S,V;
    V=(4*PI*pow(r,3))/3;
    S=4*PI*pow(r,2);
    printf("球的表面积为：%f，体积为%f",S,V);
    return 0;
}