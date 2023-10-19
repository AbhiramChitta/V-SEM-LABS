l1=[1,2,3,4,5]
l2=[6,7,8,9,10]
l3=[]
for elem in l1:
    if (elem%2!=0):
        l3.append(elem)
for elem in l2:
    if (elem%2==0):
        l3.append(elem)
print(l3)


