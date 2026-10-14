#include <stdio.h>
#include <windows.h>

void judge_by_if(double t)
{
    if (t < 18)
        printf("低体重\n");
    if (t >= 18 && t < 25)
        printf("正常体重\n");
    if (t >= 25 && t < 27)
        printf("超重体重\n");
    if (t >= 27)
        printf("肥胖\n");
}

void judge_by_ifelse(double t)
{
    if (t < 18)
        printf("低体重\n");
    else if (t < 25)
        printf("正常体重\n");
    else if (t < 27)
        printf("超重体重\n");
    else
        printf("肥胖\n");
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    double h, w, t;
    scanf("%lf %lf", &h, &w);

    t = w / (h * h);
    printf("体指数 t = %.2f\n", t);
    judge_by_if(t);
    judge_by_ifelse(t);

    return 0;
}
