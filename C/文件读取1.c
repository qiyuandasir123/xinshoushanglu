#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
int main(void){
    SetConsoleOutputCP(65001);
    FILE *fp=fopen("C:\\Users\\jianan\\Desktop\\try.txt", "rb");
    if(fp==NULL){
        printf("文件打开失败");
        return 1;
    }
    fseek(fp,0,SEEK_END);
    long size=ftell(fp);
    if(size<=0){
        printf("获取文件大小失败\n");
        fclose(fp);
        return 1;
    }
    fseek(fp,0,SEEK_SET);
    char *buf=(char*)malloc(size+1);
    if(buf==NULL){
        printf("内存分配失败\n");
        fclose(fp);
        return 1;
    }
    fread(buf,1,size,fp);
    buf[size]='\0';
    puts(buf);
    fclose(fp);
    free(buf);
    return 0;
}