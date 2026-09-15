T=input("请输入每日进步值:")
up=1
for i in range(365):
    if i %7 in [0,6]:
        up=up*(1-float(T))
    else :
        up=up*(1+float(T))
print("工作日进步值：{:.2f}".format(up))
input()