#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char s[] = "Hello World";
    char *p = strchr(s, 'l');
    char *t = (char *)malloc(strlen(p) + 1);
    strcpy(t, p);
    char c=*p;
    *p='\0';
    printf("%s\n", s);
    free(t);
    return 0;
}