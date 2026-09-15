#include <stdio.h>
#include <windows.h>
#include <math.h>
int main()
{
    double ben, desposite, rate;
    SetConsoleOutputCP(65001);
    ben = 12345;
    rate = 0.0225;
    desposite = ben * pow((1 + rate), 5);
    printf("5年后本息和为:%lf\n", desposite);
    return 0;
}