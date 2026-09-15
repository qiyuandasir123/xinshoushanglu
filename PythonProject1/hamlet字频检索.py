def get():
    with open(r"C:\Users\jianan\Downloads\hamlet.txt", 'r', encoding='utf-8') as f:
        txt = f.read()
    txt=txt.lower()
    a='''~`!@#$%^&*()_+-={}|[]:"'<>?,./'''
    for i in a:
        txt=txt.replace(i,'')
    return txt
count={}
txt=get()
words=txt.split()
for word in words:
    count[word]=count.get(word,0)+1
a=list(count.items())
a.sort(key=lambda x:x[1],reverse=True)
for i in a:
    word,freq=i
    print('{}：{}'.format(word,freq))
