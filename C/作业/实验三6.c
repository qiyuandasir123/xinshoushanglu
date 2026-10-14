#include <stdio.h>
#include <windows.h>

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    double amount;
    scanf("%lf", &amount);
    if (amount < 100)
    {
        printf("%.2f\n", amount);
    }
    else
    {
        printf("%.2f\n", amount - 10);
    }

    return 0;
}
