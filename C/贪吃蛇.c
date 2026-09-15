/* ==========================================================
   贪吃蛇（小白版）
   操作：方向键  或  W A S D
   吃到 * 得 10 分并变长；撞墙或撞到自己 就结束
   ========================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>   /* _kbhit() / _getch()：检测按键（Windows 自带） */
#include <windows.h> /* Sleep() 暂停、SetConsoleCursorPosition() 移动光标 */

#define W 50 /* 游戏区宽度（格子数） */
#define H 15 /* 游戏区高度（格子数） */

int snakeX[W * H]; /* 蛇每一节的横坐标，[0] 是蛇头 */
int snakeY[W * H]; /* 蛇每一节的纵坐标 */
int len = 1;       /* 蛇的长度 */
int dir = 3;       /* 方向：0=上 1=下 2=左 3=右（一开始往右） */
int foodX, foodY;  /* 食物的横纵坐标 */
int score = 0;     /* 得分 */

/* 把光标移到第 x 列、第 y 行。
   有了它，重画时不用清屏，画面就不会一闪一闪的 */
void gotoxy(int x, int y)
{
    COORD pos;
    pos.X = (SHORT)x;
    pos.Y = (SHORT)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/* 隐藏那个一闪一闪的光标 */
void hideCursor(void)
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

/* 随机放一个食物，但不能放到蛇身上 */
void newFood(void)
{
    int i, ok;
    do
    {
        ok = 1;             /* 先假设这个位置没问题 */
        foodX = rand() % W; /* % 取余，得到 0 ~ W-1 */
        foodY = rand() % H;
        for (i = 0; i < len; i++)
        { /* 逐个检查蛇身 */
            if (foodX == snakeX[i] && foodY == snakeY[i])
            {
                ok = 0; /* 压在蛇身上了，重新摇 */
            }
        }
    } while (ok == 0);
}

/* 画一帧画面 */
void draw(void)
{
    char map[H][W]; /* 一张"画布"，20 列 15 行 */
    int i, j;

    /* 第 1 步：画布全填成空格 */
    for (i = 0; i < H; i++)
        for (j = 0; j < W; j++)
            map[i][j] = ' ';

    /* 第 2 步：把食物画上去 */
    map[foodY][foodX] = '*';

    /* 第 3 步：把蛇画上去（头是 @，身体是 o） */
    for (i = 0; i < len; i++)
    {
        if (i == 0)
            map[snakeY[i]][snakeX[i]] = '@';
        else
            map[snakeY[i]][snakeX[i]] = 'o';
    }

    /* 第 4 步：打印到屏幕上（光标先回左上角） */
    gotoxy(0, 0);

    for (i = 0; i < W + 2; i++)
        putchar('#'); /* 上边框 */
    putchar('\n');

    for (i = 0; i < H; i++)
    {
        putchar('#'); /* 左边框 */
        for (j = 0; j < W; j++)
            putchar(map[i][j]);
        putchar('#'); /* 右边框 */
        putchar('\n');
    }

    for (i = 0; i < W + 2; i++)
        putchar('#'); /* 下边框 */
    printf("\nScore: %d    (Arrow keys or WASD)\n", score);
}

/* 读按键：把攒着的按键全部处理掉 */
void input(void)
{
    int ch;
    while (_kbhit())
    {                  /* 有键按下了吗？有就一直读 */
        ch = _getch(); /* 读一个键 */
        if (ch == 0 || ch == 224)
        {                  /* 方向键会先返回 0 或 224 */
            ch = _getch(); /* 再读一次才是真正的方向 */
            if (ch == 72 && dir != 1)
                dir = 0; /* ↑（不能直接掉头） */
            if (ch == 80 && dir != 0)
                dir = 1; /* ↓ */
            if (ch == 75 && dir != 3)
                dir = 2; /* ← */
            if (ch == 77 && dir != 2)
                dir = 3; /* → */
        }
        else
        { /* 字母键 */
            if ((ch == 'w' || ch == 'W') && dir != 1)
                dir = 0;
            if ((ch == 's' || ch == 'S') && dir != 0)
                dir = 1;
            if ((ch == 'a' || ch == 'A') && dir != 3)
                dir = 2;
            if ((ch == 'd' || ch == 'D') && dir != 2)
                dir = 3;
        }
    }
}

/* 蛇往前走一步 */
void move(void)
{
    int i;
    int tailX = snakeX[len - 1]; /* 先记住尾巴在哪（吃东西要在这儿接一节） */
    int tailY = snakeY[len - 1];

    /* 从尾巴开始，每一节都挪到"前一节原来的位置" */
    for (i = len - 1; i > 0; i--)
    {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    /* 蛇头按当前方向走一格 */
    if (dir == 0)
        snakeY[0]--;
    if (dir == 1)
        snakeY[0]++;
    if (dir == 2)
        snakeX[0]--;
    if (dir == 3)
        snakeX[0]++;

    /* 吃到食物了？ */
    if (snakeX[0] == foodX && snakeY[0] == foodY)
    {
        score = score + 10;
        snakeX[len] = tailX; /* 在老尾巴处接一节 → 蛇变长 */
        snakeY[len] = tailY;
        len++;
        newFood(); /* 再放一个新食物 */
    }
}

/* 判断游戏是否结束：1 = 结束，0 = 还活着 */
int isOver(void)
{
    int i;
    if (snakeX[0] < 0 || snakeX[0] >= W)
        return 1; /* 左右撞墙 */
    if (snakeY[0] < 0 || snakeY[0] >= H)
        return 1; /* 上下撞墙 */
    for (i = 1; i < len; i++)
    { /* 头撞到自己身体 */
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
            return 1;
    }
    return 0;
}

int main(void)
{
    srand((unsigned)time(NULL)); /* 用当前时间当"种子"，食物位置才随机 */

    snakeX[0] = W / 2; /* 蛇头一开始放中间 */
    snakeY[0] = H / 2;
    len = 1;
    dir = 3; /* 一开始往右 */
    score = 0;

    newFood();    /* 放第一个食物 */
    hideCursor(); /* 关掉光标 */

    while (1)
    {
        input(); /* 1. 收按键 */
        move();  /* 2. 走一步 */
        if (isOver())
            break;  /* 3. 撞了就跳出循环 */
        draw();     /* 4. 重画画面 */
        Sleep(150); /* 5. 等 150 毫秒：数字越小蛇越快 */
    }

    gotoxy(0, H + 3);
    printf("Game Over! Final score: %d\n", score);
    printf("Press any key to exit...");
    _getch(); /* 等一个按键，别让窗口一闪就关 */
    return 0;
}