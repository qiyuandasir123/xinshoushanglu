#include <stdio.h>
#include <windows.h>
int main(){
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    struct date {
        int year;
        int month;
        int day;
    }d1,d2;
    d1.year = 2020;
    d1.month = 1;
    d1.day = 1;
    d2.year=2026;
    d2.month=10;
    d2.day=1;
    printf("%d %d %d\n", d1.year, d1.month, d1.day);
    printf("%d %d %d\n", d2.year, d2.month, d2.day);

    return 0;
}