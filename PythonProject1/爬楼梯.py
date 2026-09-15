count=0
def f(n):
    global count
    if n==1:
        count+=1
        return 1
    elif n==2:
        count+=1
        return 2
    else:
        count+=1
        return f(n-1)+f(n-2)

f(4)
print(count)
