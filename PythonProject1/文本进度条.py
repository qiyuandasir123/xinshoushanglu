import time
print("执行开始".center(100,"-"))
for i in range(101):
    start=time.perf_counter()
    end=time.perf_counter()
    d=start-end
    a=i
    b="*"*i
    c=(100-i)*"-"
    print("\r{}%[{}->{}]{:.2f}".format(a,b,c,d),end=' ')
    time.sleep(0.1)
print("\n"+"执行结束".center(100,"-"))
time.sleep(12)