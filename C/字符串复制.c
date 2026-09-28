#include <stdio.h>
#include <string.h>
char *mycpy(char*dst,char*rst){
    int idx=0;
    while (1){
        if (rst[idx]=='\0'){
            break;
        }dst[idx]=rst[idx];
        idx++;
    }
    dst[idx] = '\0';   /* 是反斜杠零，不是字符 '0' */
    return dst;
}
int main()
{
    char s1[5]="hello";
    char *s2="World";
    mycpy(s1,s2);
    printf("%s",s1);
    printf("%s",s2);
    return 0;
}