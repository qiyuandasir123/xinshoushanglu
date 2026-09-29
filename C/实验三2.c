#include <stdio.h>
#include <windows.h>

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    int a, b;
    scanf("%d %d", &a, &b);
    if (a > b)
    {
        printf("%d\n", a);
    }
    else
    {
        if (a == b)
            printf("equal\n");
        else
            printf("%d\n", b);
    }
    return 0;
}
