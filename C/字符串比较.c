#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
int main(void)
{
    char *a = "Hello";
    for (int i = 0; i < strlen(a); i++)
    {
        printf("%c", a[i]);
    }
    char *s1="abc";
    char *s2="Abc";
    printf("%d",strcmp(s1,s2));
    printf("%d",s1-s2);
    return 0;
}
