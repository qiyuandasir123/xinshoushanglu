/* Bad Apple!! 字符动画
 * 编译: gcc badapple.c -o badapple.exe -O2 -lwinmm
 * 运行: 双击 exe，或在 VS Code 里按运行键 —— 都能跑
 *
 * 会自动在 3 个位置里找 txt 文件夹，所以 VS Code 用什么工作目录都不怕:
 *     1) 和 exe 同一个文件夹      （C:\...\C\txt）
 *     2) 当前工作目录             （VS Code 的 cwd\txt）
 *     3) 当前工作目录的上一级     （VS Code 的 cwd\..\txt）
 * 判断依据是哪个位置真的有 txt\1.txt。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>

#define COLS 120
#define ROWS 45

/* 探测可用的 txt 文件夹，把路径前缀写进 out */
static void find_txt(char *out, size_t n)
{
    char exe[512], base[600], cand[700];
    GetModuleFileNameA(NULL, exe, sizeof exe);      /* exe 自己的完整路径 */
    char *s = strrchr(exe, '\\');
    if (s) *s = 0;                                  /* 去掉文件名，剩下目录 */

    for (int k = 0; k < 3; ++k) {
        if (k == 0) snprintf(base, sizeof base, "%s\\txt", exe);  /* exe 同级 */
        else if (k == 1) snprintf(base, sizeof base, "txt");      /* 当前目录 */
        else snprintf(base, sizeof base, "..\\txt");              /* 上一级 */

        snprintf(cand, sizeof cand, "%s\\1.txt", base);
        FILE *f = fopen(cand, "r");
        if (f) { fclose(f); snprintf(out, n, "%s", base); return; }
    }
    snprintf(out, n, "txt");                        /* 都没有就退回默认 */
}

int main(void) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD home = {0, 0};
    char dir[600], path[800], buf[COLS + 8];
    long frames = 6573, i;

    find_txt(dir, sizeof dir);

    snprintf(path, sizeof path, "%s\\_count.txt", dir);   /* 帧数（可选） */
    FILE *cf = fopen(path, "r");
    if (cf) { fscanf(cf, "%ld", &frames); fclose(cf); }

    SMALL_RECT r = {0, 0, 1, 1};
    SetConsoleWindowInfo(h, TRUE, &r);                   /* 先把窗口缩小 */
    SetConsoleScreenBufferSize(h, (COORD){COLS, ROWS});  /* 缓冲区=一帧，不滚屏 */
    r = (SMALL_RECT){0, 0, COLS - 1, ROWS - 1};
    SetConsoleWindowInfo(h, TRUE, &r);                   /* 窗口撑到整帧 */

    timeBeginPeriod(1);                                  /* 1ms 精度，才是真 30fps */
    LARGE_INTEGER f, t0, t;
    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t0);

    for (i = 1; i <= frames; i++) {
        snprintf(path, sizeof path, "%s\\%ld.txt", dir, i);
        FILE *fp = fopen(path, "r");
        if (fp) {
            SetConsoleCursorPosition(h, home);           /* 回左上角原位覆盖 */
            while (fgets(buf, sizeof buf, fp)) fputs(buf, stdout);
            fclose(fp);
        }
        while (1) {                                      /* 精确对帧，误差不累积 */
            QueryPerformanceCounter(&t);
            if ((double)(t.QuadPart - t0.QuadPart) / f.QuadPart >= i / 30.0) break;
            Sleep(1);
        }
    }
    timeEndPeriod(1);
    return 0;
}
