class Dog:
    price='100$'
    def __init__(self,name,age):
        self.name=name
        self.age=age
    def sit(self):
        print(f"{self.name}在坐着")
    def rollover(self):
        print(f"{self.name}在打滚")
b=[]
while True:
    name=input("请输入名字：")
    if name=='':
        break
    age=int(input("请输入年龄："))
    a=Dog(name,age)
    b.append(a)
for i in b:
    i.sit()
    i.rollover()
     