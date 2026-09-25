#include <stdio.h>
#include <windows.h>
int main(int argv, char const *argc[])
{   
    SetConsoleOutputCP(65001);
    int i=0;
    for (i=0; i<argv; i++){
        printf("%d :%s\n", i,argc[i]);

    }
    return 0;
}
    
    