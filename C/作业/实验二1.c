#include <stdio.h>
#include <windows.h>
#define change 1.60934
int main(){
    SetConsoleOutputCP(65001);
    float g;
    printf("请输入公里数：");
    scanf("%f",&g);
    float y;
    y=g/change;
    printf("英里数为：%f\n",y);
    return 0;
}
