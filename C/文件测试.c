#include <stdio.h>
#include <windows.h>
int main()
{
    SetConsoleOutputCP(65001);
    FILE *fp=fopen("C:/Users/jianan/Desktop/try.txt","r");
    if(fp){
        int i;
        printf("文件打开成功\n");
        fscanf(fp,"%d",&i);
        printf("%d\n",i);
        fclose(fp);
    }else{
        printf("文件打开失败\n");
    }
    return 0;
}