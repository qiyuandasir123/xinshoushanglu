import random as r
import time as t
start= t.perf_counter()
dur= t.perf_counter()-start
total=1000*1000
a=0
for i in range(total):
    x,y=r.random(),r.random()
    if pow(pow(x,2)+pow(y,2),0.5)<=1:
        a+=1
pi=4*a/total
print('圆周率是：{:.2f}   {}'.format(pi,dur))
a=0
for i in range(1,967,2):
    a=a+i-(i+1)
print('a')