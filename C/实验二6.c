#include <stdio.h>
#include <windows.h>
int main()
{
    double F;
    scanf("%lf",&F);
    double C=5*(F-32)/9;
    printf("%.5f\n",C);
    return 0;
}