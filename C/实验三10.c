#include <stdio.h>
#include <windows.h>

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    int weight, fee;
    char urgent;
    scanf("%d %c", &weight, &urgent);
    fee = 8;
    if (weight > 1000)
    {
        int over = weight - 1000;
        int units = (over + 499) / 500;
        fee = fee + units * 4;
    }
    if (urgent == 'y')
        fee = fee + 5;
    printf("%d\n", fee);
    return 0;
}
