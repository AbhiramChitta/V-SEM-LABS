import re
f1=open("input.txt","w")
f1.write("abhichitta03@gmail.com\n")
f1.write("prashanth@gmail.com\n")
f1.write("pavantej\n")
f1.write("abhichitta03\n")
f1.close()
f1=open("input.txt","r")
f2=open("valid.txt","w")
for line in f1:
    if(re.search(r'@gmail.com',line,re.M|re.I)):
        f2.write(line+"\n")
