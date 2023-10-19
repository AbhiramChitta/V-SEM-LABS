n=input("number1?")
m=input("number2?")
for i in range(int(n),int(m)):
    for j in range(2,int(i/2)):
        if((i%j)==0):
            break
    else:
        print(i)
