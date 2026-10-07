#include <stdio.h>
#include <windows.h>
int main(){
    SetConsoleOutputCP(65001);
    printf("For sprintf:\n");
    char str[114514];
    sprintf(str,"Hello World");
    printf("%s\n",str);
    printf("For snprintf:\n");
    char str1[114514];
    snprintf(str1,sizeof(str1),"Hello World");
    printf("%s\n",str1);
    return 0;
}