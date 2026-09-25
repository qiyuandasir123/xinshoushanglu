#include <stdio.h>
#include <windows.h>
int main()
{
    SetConsoleCP(65001);        /* 输入代码页：让 getchar 拿到 UTF-8 字节 */
    SetConsoleOutputCP(65001);  /* 输出代码页：让控制台按 UTF-8 解码 */
    int c;
    while ((c = getchar()) != EOF)
    {
        putchar(c);

    }
    return 0;
}