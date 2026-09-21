#include <stdio.h>

int main()
{
    int a = 2;
    int b = 2;
    int c[a][b];
    c[0][0] = 1;
    c[0][1] = 2;
    c[1][0] = 3;
    c[1][1] = 4;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
            printf("%d", c[i][j]);
    }

    return 0;
}