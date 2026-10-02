#include <stdio.h>
#include <windows.h>
union date{
    int year;
    int month;
    int day;
};
int main(){
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    union date d1={2026};
    printf("%d\n", d1.year);
    d1.month=10;
    printf("%d\n", d1.month);
    union date d2;
    d2.day=1;
    d2.month=10;
    printf("%d\n%d\n", d2.day, d2.month);

    return 0;
}