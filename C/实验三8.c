#include <stdio.h>
#include <windows.h>

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int year, month, days;
    scanf("%d %d", &year, &month);

    int leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        days = 31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        days = 30;
        break;
    case 2:
        if (leap)
            days = 29;
        else
            days = 28;
        break;
    default:
        days = 0;
        break;
    }

    if (days == 0)
        printf("月份输入有误，请输入 1~12\n");
    else
        printf("%d 年 %d 月有 %d 天\n", year, month, days);

    return 0;
}
