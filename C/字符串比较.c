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
    return 0;
}
