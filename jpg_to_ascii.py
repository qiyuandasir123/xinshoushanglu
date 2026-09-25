# -*- coding: utf-8 -*-
"""把 JPG 帧批量转成 ASCII 字符 txt（纯 Python + Pillow，不需要 Ascgen2 / .NET 3.5）。"""
import os, sys, io, glob, time
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
from PIL import Image

SRC  = r"C:\whale girl1day\badapple\picture"
DST  = r"C:\whale girl1day\badapple\txt"
COLS = 120          # 每行字符数
ROWS = 45           # 行数（保持 8:3；字符格约 2 倍高，画面才不变形）
RAMP = " .:-=+*#%@" # 亮->密；黑剪影会变成密集字符

os.makedirs(DST, exist_ok=True)

def num(p):
    d = ''.join(c for c in os.path.basename(p) if c.isdigit())
    return int(d) if d else 0

files = sorted(glob.glob(os.path.join(SRC, "*.jpg")), key=num)
print("source frames:", len(files))
if not files:
    sys.exit("no jpg frames found")

# 亮度 0..255 -> 字符，黑(v=0)取最密字符
lut = bytes((255 - i) * (len(RAMP) - 1) // 255 for i in range(256))
table = bytes(ord(RAMP[lut[i]]) for i in range(256))

t0 = time.time()
written = 0
for idx, f in enumerate(files, 1):
    im = Image.open(f).convert('L').resize((COLS, ROWS), Image.LANCZOS)
    mapped = im.tobytes().translate(table)          # ROWS*COLS 个 ASCII 字节
    # 每行固定 COLS 字符、不裁剪：这样 C 里直接 fgets+fputs 就不会有残影
    lines = [mapped[y * COLS:(y + 1) * COLS] for y in range(ROWS)]
    with open(os.path.join(DST, "%d.txt" % idx), "wb") as fh:
        fh.write(b"\n".join(lines) + b"\n")
    written += 1
    if idx % 1000 == 0:
        print("  %d/%d  %.1fs" % (idx, len(files), time.time() - t0))

with open(os.path.join(DST, "_count.txt"), "w") as fh:
    fh.write(str(written))
print("done: %d txt files, %.1fs, size=%dx%d" % (written, time.time() - t0, COLS, ROWS))
