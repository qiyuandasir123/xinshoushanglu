#include <stdio.h>
#include <windows.h>
int main(int argv, char const *argc[])
{   
    int i=0;
    i++;
    printf("%d\n",i);
    for (i=0; i<argv; i++){
        printf("%d :%s\n", i,argc[i]);

    }
    return 0;
}
    
    