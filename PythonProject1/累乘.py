def cmul(a, *b):
    m = a
    for i in b:
        m*=i
    return m

print(eval("cmul({})".format(input())))