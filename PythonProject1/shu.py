import turtle as t


def draw_tree(branch_len, n):
    # 1. 基准情况：如果当前树枝长度小于 5，就不画了，直接返回（停止递归）
    if branch_len < 5:
        return

    # 2. 画当前主干
    t.forward(branch_len)

    # 3. 先画左侧分支
    t.left(40)  # 左转 40 度
    draw_tree(branch_len - n, n)  # 递归，长度减去 n
    t.right(40)  # 角度复原

    # 4. 再画右侧分支
    t.right(40)  # 右转 40 度
    draw_tree(branch_len - n, n)  # 递归
    t.left(40)  # 角度复原

    # 5. 画完后，原路退回起点！（灵魂一步）
    t.backward(branch_len)


# 初始化窗口
t.setup(1500, 1000, 0, 0)
t.speed(5)  # 画笔速度，0最快，5适中
t.penup()
t.goto(0, -500)  # 起点放到屏幕下方
t.pendown()
t.pencolor('green')
t.pensize(3)
t.seth(90)  # 海龟朝正上方

# 调整初始长度和每次减少的长度，可以控制树的茂密程度
initial_len = 80  # 初始长度（建议 60~100）
decay = 10  # 每次长度减多少

# 开始画
draw_tree(initial_len, decay)

# 画完隐藏海龟箭头
t.hideturtle()

# 只有在程序的最后，才使用 t.done() 来保持窗口不关闭
t.done()