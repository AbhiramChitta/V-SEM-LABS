def main():
    k = input("Enter string: ")
    case(k)


def case(str1):
    upper = 0
    lower = 0
    for i in str1:
        if i.islower():
            lower += 1
        elif i.isupper():
            upper += 1
    print(("lower case char= ", lower))
    print(("upper case char= ", upper))


main()
