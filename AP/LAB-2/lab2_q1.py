def countwords(str):
    k = dict()
    words = str.split()
    for i in words:
        if i in k:
            k[i] += 1
        else:
            k[i] = 1
    print(k)


def main():
    str = input("Enter string: ")
    countwords(str)


main()
