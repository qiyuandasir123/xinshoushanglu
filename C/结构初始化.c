#include <stdio.h>
#include <windows.h>
struct date{
        int year;
        int month;
        int day;
    };
int main(){
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    printf("法一：\n");
    
    struct date d1={2026,10,1};
    printf("Date: %d-%d-%d\n", d1.year, d1.month, d1.day);
    printf("法二：\n");
    struct date d2;
    d2.year=2026;
    d2.month=10;
    d2.day=1;
    printf("Date: %d-%d-%d\n", d2.year, d2.month, d2.day);
    printf("法三：\n");
    struct date d3={.year=2026,.month=10,.day=1};
    printf("Date: %d-%d-%d\n", d3.year, d3.month, d3.day);
    printf("法四：\n");
    struct date d4;
    d4=(struct date){2026,10,1};
    printf("Date: %d-%d-%d\n", d4.year, d4.month, d4.day);
    printf("法五：指针法：\n");
    struct date d5;
    struct date *p=&d5;
    p->year=2026;
    p->month=10;
    p->day=1;
    printf("Date: %d-%d-%d\n", p->year, p->month, p->day);
    printf("法六：指针赋值：\n");
    struct date d6;
    struct date *pd6=&d6;
    *pd6=(struct date){2026,10,1};
    printf("Date: %d-%d-%d\n", pd6->year, pd6->month, pd6->day);
    printf("法七：指针返回结构整体赋值：\n");
    struct date d7;
    struct date *pd7=&d7;
    numberofd6(pd7);
    printf("Date: %d-%d-%d\n", pd7->year, pd7->month, pd7->day);
    return 0;
}
int numberofd6(const struct date *p){
    scanf("%d %d %d", &p->year, &p->month, &p->day);
    return p;
}
