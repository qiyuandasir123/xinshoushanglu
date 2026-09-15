import turtle as t
def ks(len,n):
    if n==0:
        t.fd(20)
    else:
        for angle  in [0,60,-120,60]:
            t.left(angle)
            ks(len/3,n-1)
t.setup(1500,1000,0,0)
t.penup()
t.goto(-300,0)
t.pendown()
t.pensize(5)
t.pencolor('blue')
len=20
n=3
t.pendown()
ks(len,n)
t.right(120)
ks(len,n)
t.right(120)
ks(len,n)
import time
time.sleep(12)