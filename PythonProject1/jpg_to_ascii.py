# -*- coding: utf-8 -*-
"""
JPG 帧 -> ASCII 字符 txt  批量转换（通用版 / 可零参数运行）

最简用法（不带任何参数）:
    python jpg_to_ascii.py

    会自动做三件事：
      1. 在 C:\\Users\\jianan\\Videos 下找"jpg 最多的那个文件夹"当作输入
      2. 输出到 <本脚本目录>\\..\\C\\txt
      3. 每行 120 字符；行数按图片比例自动算，保证画面不变形

想手动指定:
    python jpg_to_ascii.py <图片文件夹> <输出文件夹> [每行字符数]

例:
    python jpg_to_ascii.py "C:\\Users\\jianan\\Videos\\xxx帧" "D:\\code\\C\\txt" 120

说明:
    - 每行固定宽度（不裁行尾空格），这样 C 里 fgets + fputs 就不会有残影
    - 输出文件名是 1.txt 2.txt 3.txt ...，并额外写一个 _count.txt 记录总帧数
"""
import os
import re
import sys
import io
import glob
import time

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
from PIL import Image

RAMP = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"               # 亮 -> 密：黑的地方用密集字符，白的用空格
VIDEO_ROOT = r"C:\Users\jianan\Videos"
DEF_COLS = 120

HERE = os.path.dirname(os.path.abspath(__file__))


def frame_no(path):
    """取文件名结尾的数字作为帧号（避免被文件名里其它数字干扰）"""
    m = re.search(r'(\d+)(?=\.[^.]+$)', os.path.basename(path))
    return int(m.group(1)) if m else 0


def auto_input():
    """在 VIDEO_ROOT 下找帧文件夹：优先"最近修改过的"，并打印所有候选供核对"""
    if not os.path.isdir(VIDEO_ROOT):
        return None
    cands = []
    for name in os.listdir(VIDEO_ROOT):
        full = os.path.join(VIDEO_ROOT, name)
        if not os.path.isdir(full):
            continue
        jpgs = glob.glob(os.path.join(full, '*.jpg'))
        if not jpgs:
            continue
        newest = max(os.path.getmtime(p) for p in jpgs)
        cands.append((newest, len(jpgs), full))
    if not cands:
        return None
    cands.sort(reverse=True)                 # 最近修改的排最前
    if len(cands) > 1:
        print("发现 %d 个含 jpg 的文件夹（按最近修改排序）:" % len(cands))
        for t, n, full in cands:
            mark = "  <== 选中" if full == cands[0][2] else ""
            print("   %s\n       %d 张, 最后修改 %s%s"
                  % (full, n, time.strftime('%Y-%m-%d %H:%M', time.localtime(t)), mark))
    return cands[0][2]


def main():
    args = sys.argv[1:]

    if len(args) >= 2:
        src, dst = args[0], args[1]
        cols = int(args[2]) if len(args) > 2 else DEF_COLS
    elif len(args) == 0:
        src = auto_input()
        if not src:
            print("没在 %s 下找到含 jpg 的文件夹，请手动指定参数" % VIDEO_ROOT)
            print(__doc__)
            return 1
        # 输出到 本脚本目录\..\C\txt
        dst = os.path.normpath(os.path.join(HERE, '..', 'C', 'txt'))
        cols = DEF_COLS
        print("（未给参数，自动选择）")
    else:
        print(__doc__)
        return 1

    files = sorted(glob.glob(os.path.join(src, '*.jpg')), key=frame_no)
    if not files:
        print("没找到 jpg：%s" % src)
        return 1

    # 行数 = 列数 * (图高/图宽) / 2，其中 2 是字符格的高宽比
    w, h = Image.open(files[0]).size
    rows = max(1, int(round(cols * h / (2.0 * w))))

    print("输入目录: %s" % src)
    print("输出目录: %s" % dst)
    print("帧数: %d   图片: %dx%d   输出网格: %d列 x %d行" % (len(files), w, h, cols, rows))

    os.makedirs(dst, exist_ok=True)

    # 亮度 0..255 -> 字符，黑(v=0) 取最密字符
    lut = bytes((255 - i) * (len(RAMP) - 1) // 255 for i in range(256))
    table = bytes(ord(RAMP[lut[i]]) for i in range(256))

    t0 = time.time()
    for idx, f in enumerate(files, 1):
        im = Image.open(f).convert('L').resize((cols, rows), Image.LANCZOS)
        mapped = im.tobytes().translate(table)
        lines = [mapped[y * cols:(y + 1) * cols] for y in range(rows)]
        with open(os.path.join(dst, "%d.txt" % idx), "wb") as fh:
            fh.write(b"\n".join(lines) + b"\n")
        if idx % 500 == 0:
            print("  %d/%d  %.1fs" % (idx, len(files), time.time() - t0))

    with open(os.path.join(dst, "_count.txt"), "w") as fh:
        fh.write(str(len(files)))

    print("完成: %d 个 txt, 用时 %.1fs, 网格 %dx%d" % (len(files), time.time() - t0, cols, rows))
    print(">>> 记得把 C 代码改成:  #define COLS %d   #define ROWS %d" % (cols, rows))
    return 0


if __name__ == '__main__':
    sys.exit(main())
