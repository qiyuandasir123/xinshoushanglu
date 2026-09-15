def f(a):
    if a<=1:
        return str(a)
    else:
        return str(f(a//2))+str(a%2)
a=int(input())
print(f(a))


