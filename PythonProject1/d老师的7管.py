import turtle as t
import time


def line(d):
    t.pendown() if d else t.penup()
    t.fd(50)
    t.right(90)


def draw(shu):
    line(True) if shu in ['2', '3', '4', '5', '6', '8', '9'] else line(False)
    line(True) if shu in ['0', '1', '3', '4', '5', '6', '7', '8', '9'] else line(False)
    line(True) if shu in ['0', '1', '3', '4', '5', '6', '7', '8', '9'] else line(False)
    line(True) if shu in ['0', '1', '2', '3', '4', '7', '8', '9'] else line(False)
    t.left(90)
    line(True) if shu in ['0', '2', '6', '8'] else line(False)
    line(True) if shu in ['0', '4', '5', '6', '8', '9'] else line(False)
    line(True) if shu in ['2', '3', '4', '5', '6', '8', '9'] else line(False)

    t.left(180)
    t.penup()
    t.fd(50)

    if shu in ['-', '=', '!']:
        t.left(90)
        t.fd(5)
        t.begin_fill()
        for i in range(4):
            t.fd(5)
            t.right(90)
        t.end_fill()
        t.right(180)
        t.fd(10)
        t.begin_fill()
        for i in range(4):
            t.fd(5)
            t.left(90)
        t.end_fill()
        t.left(180)
        t.fd(5)
        t.right(90)
        t.fd(50)  # 🟢 关键：把这里从 100 改成 50


def draw2(date):
    for i in date:
        draw(i)


t.setup(1700, 1000, 0, 0)
t.pensize(10)
t.pencolor('blue')
t.tracer(0)

while True:
    t.clear()  # 1. 先清空上一帧的图
    t.penup()
    t.goto(-800, 0)  # 2. 重新回到左边的起点

    a = time.localtime()
    date = time.strftime('%H-%M=%S', a)
    draw2(date)  # 3. 画新的时间

    t.update()  # 4. 一次性刷新屏幕
    time.sleep(1)  # 5. 停顿1秒