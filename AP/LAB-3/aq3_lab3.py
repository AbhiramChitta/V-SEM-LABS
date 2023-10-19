def func(b):
    def func1(a):
        return a+b
    return func1


def main():
    c = func(10)
    print(c(5))


main()
