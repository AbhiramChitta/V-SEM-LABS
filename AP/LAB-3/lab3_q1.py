def Input():
    list1 = []
    n = int(input("Enter no. values in the list: "))
    for i in range(n):
        ele = int(input("enter value:"+str(i+1)+" "))
        list1.append(ele)
    multiply(list1)


def multiply(list1):
    mul = 1
    for i in list1:
        mul *= i
    print(mul)


def main():
    Input()


main()
