a = int(input())
b = 'Hello World'
if a == 0:
    print("Hello World")
elif a > 0:
    for i in range(0,len(b),2):
        print(b[i:i+2])
else:
        for i in b:
            print(i)


