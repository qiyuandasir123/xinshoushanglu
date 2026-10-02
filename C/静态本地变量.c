#include <stdio.h>
#include <windows.h>
int main(){
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    printf("若在函数中使用静态本地变量：\n");
    f();
    f();
    f();
    printf("若在主函数中使用静态本地变量：\n");
    static int b=0;
    b++;
    return 0;
}
int f(void){
    static int a=0;
    a++;
    printf("a=%d\n", a);
}