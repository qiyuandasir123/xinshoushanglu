pi=0
for k in range(125):
    pi+=(4/(8*k+1)-2/(8*k\
    +4)-1/(8*k+5)\
    -1/(8*k+6))/pow(16,k)
print(pi)