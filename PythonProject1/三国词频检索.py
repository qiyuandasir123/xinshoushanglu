import jieba as j
def get():
    txt=open(r"C:\Users\jianan\Downloads\《三国演义》【爱上阅读_www.isyd.net】.txt", 'r', encoding='utf-8').read()
    a=j.lcut(txt)
    return a
discard={'将军','却说','二人','荆州','不可','不能','如此'}
a=get()
b={}
for i in a:
    if len(i)==1:
        continue
    elif i=='诸葛亮' or i=='孔明曰':
         rword='孔明'
    elif i=='关公' or i=='云长':
        rword='关羽'
    elif i=='玄德' or i=='玄德曰':
         rword='刘备'
    elif i == '孟德' or i=='丞相'or i=='曹操曰':
          rword = '曹操'
    elif i in discard:
        continue
    else:
          rword=i
    b[rword]=b.get(rword,0)+1
m=list(b.items())
m.sort(key=lambda x:x[1],reverse=True)
for i in m:
    name,freq=i
    print('{}:{}'.format(name,freq))


