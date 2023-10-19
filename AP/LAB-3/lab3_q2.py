def Input(list1):
    list2 = []
    for i in list1:
        if i not in list2:
            list2.append(i)
    return list2


def main():
    list1 = []
    n = int(input("Enter no. values in the list: "))
    for i in range(n):
        ele = int(input("enter value:"+str(i+1)+" "))
        list1.append(ele)
    list3 = Input(list1)
    print(list3)


main()
