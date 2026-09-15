#include <windows.h>
#include <stdio.h>
int main()
{
  SetConsoleOutputCP(65001);
  int a, b = 0;
  while (++a > 0)
    ;
  b = a - 1;
  printf("最大数为：%d", b);
  return 0;
}