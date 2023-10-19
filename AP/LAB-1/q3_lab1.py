n=input("NO. OF STRINGS?")
l=[]
for i in range( int (n)):
    str=input()
    l.append(str)
count=0;
for str in l:
    if(len(str)>2):
        if(str[0]==str[-1]):
            count+=1;
print(count)
for str in l:
    if(len(str)%2):
       print(str)


