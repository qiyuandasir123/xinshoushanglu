import time
import math 
print("执行开始".center(100,"-"))
for i in range(157):
    e=int(100*math.sin(i*0.01))
    start=time.perf_counter()
    end=time.perf_counter()
    d=start-end
    a=e
    b="*"*e
    c=(100-e)*"-"
    print("\r{}%[{}->{}]{:.2f}".format(a,b,c,d),end=' ')
    time.sleep(0.1)
print("\n"+"执行结束".center(100,"-"))
time.sleep(12)