#include <stdio.h>
#include <windows.h>

enum date
{
    MON,
    TUE,
    WED,
    THU,
    FRI,
    SAT,
    SUN
};
int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    int date;
    scanf("%d", &date);

    switch (date - 1)
    {
    case MON:
        printf("NO\n");
        break;
    case TUE:
        printf("YES\n");
        break;
    case WED:
        printf("NO\n");
        break;
    case THU:
        printf("YES\n");
        break;
    case FRI:
        printf("NO\n");
        break;
    case SAT:
        printf("YES\n");
        break;
    case SUN:
        printf("YES\n");
        break;
    }

    return 0;
}
