#include <stdio.h>
#include <windows.h>

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    int N;
    scanf("%d", &N);
    if (N > 0)
    {
        printf("positive\n");
    }
    else if (N < 0)
    {
        printf("negative\n");
    }
    else
    {
        printf("zero\n");
    }
    return 0;
}
