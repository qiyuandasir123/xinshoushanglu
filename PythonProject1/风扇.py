import turtle as T
T.setup(1200,800,120,120)
T.penup()
T.pensize(20)
T.pencolor("black")
T.pendown()
for i in range(4):
    T.fd(150)
    T.right(90)
    T.circle(-150,45)
    T.right(90)
    T.fd(150)
    T.left(135)
T.done()