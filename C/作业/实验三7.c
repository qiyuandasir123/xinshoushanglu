#include <stdio.h>
#include <windows.h>

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    char a;
    scanf(" %c", &a);
    if (a >= 'A' && a <= 'Z')
    {
        printf("%c\n%d\n", a + 32, a + 32);
    }
    else if (a >= 'a' && a <= 'z')
    {
        printf("%c\n%d\n", a - 32, a - 32);
    }
    else
    {
        printf("%d\n", a);
    }
    return 0;
}
