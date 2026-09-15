import turtle as t
import time
import csv
t.setup(1500,800,0,0)
t.pensize(5)
t.speed(1)
f=open(r"C:\Users\jianan\Desktop\轨迹.csv",encoding="utf-8",mode="r")
data=[]
for line in csv.reader(f):
    data.append(list(map(float,line)))
f.close()
for i in range(len(data)):
    t.pencolor(data[i][1],data[i][2],data[i][3])
    if data[i][0]==0:
        t.penup()
    elif data[i][0]==1:
        t.pendown()
    
    if data[i][4]==0:
        t.left(data[i][5])
    elif data[i][4]==1:
        t.right(data[i][5])
    t.fd(data[i][6])
t.hideturtle()
time.sleep(2)
