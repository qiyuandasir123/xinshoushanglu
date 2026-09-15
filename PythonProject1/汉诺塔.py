count=0
def hano(n,a,c,b):
    global count
    if n==1:
        print('{}:{}->{}'.format(n,a,b))
        count+=1
        return
    else:
        hano(n-1,a,b,c)
        print('{}:{}->{}'.format(n,a,b))
        count+=1
        hano(n-1,c,a,b)
hano(2,'a','c','b')
print(count)
