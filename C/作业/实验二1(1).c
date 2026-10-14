#include <stdio.h>
#include <windows.h>
int main(){
    SetConsoleOutputCP(65001);
    float g;
    const float change=1.60934;
    printf("请输入公里数：");
    scanf("%f",&g);
    float y;
    y=g/change;
    printf("英里数为：%f\n",y);
    return 0;
}
