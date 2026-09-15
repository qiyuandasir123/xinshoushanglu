def z(s):
    c=''
    b=int(s)
    while b>=2:
        d='{}'.format(b%2)
        c=d+c
        b=b//2
    c="{}".format(b)+c
    print(c)
a=input()
z(a)
