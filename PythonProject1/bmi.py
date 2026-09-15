height,weight=eval(input())
bmi=weight/(height**2)
print('BMI数值为:{:.2f}'.format(bmi))
a='BMI指标为:'
if bmi < 18.5:
    print("{}国际'偏瘦',国内'偏瘦'".format(a))
elif 18.5<=bmi<24:
    print("{}国际'正常',国内'正常'".format(a))
elif 24<=bmi<25:
    print("{}国际'正常',国内'偏胖'".format(a))
elif 25<=bmi<28:
    print("{}国际'偏胖',国内'偏胖'".format(a))
elif 28<=bmi<30:
    print("{}国际'偏胖',国内'肥胖'".format(a))
elif 30<=bmi:
    print("{}国际'肥胖',国内'肥胖'".format(a))
