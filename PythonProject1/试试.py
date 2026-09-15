people = []
ren = {}
for i in range(int(input("请输入人数："))):
    name = input("请输入城市名：")
    age = input("地点：")
    ren["城市名"] = name
    ren["地点"] = age
    people.append(ren)
    ren = {}  
print(people)