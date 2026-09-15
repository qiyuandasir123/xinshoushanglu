import turtle as t
def z(len,n):
    if len==0:
        return
    else:
        t.fd(len)
        t.left(40)
        z(len-n,n)
        t.right(80)
        z(len-n,n)
        t.left(40)
        t.bk(len)
t.setup(1500,1000,0,0)
t.speed(0)
t.penup()
t.goto(0,-500)
t.pendown()
t.pencolor('green')
t.pensize(3)
t.seth(90)
t.fd(200)
len=50
n=5
z(len,n)
import time
time.sleep(1)

