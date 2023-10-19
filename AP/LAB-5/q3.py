class Subset:
    def __init__(self):
        self.n = []  # Initialize n as an empty list
        self.m = 0   # Initialize m as 0

    def sub(self):
        for i in range(1 << self.m):
            for j in range(self.m):
                if (i & (1 << j)) != 0:
                    print(self.n[j], end=" ")
            print()


def main():
    s = Subset()
    m = int(input("Enter the number of distinct integers: "))

    for i in range(m):
        k = int(input("Enter an integer: "))
        s.n.append(k)  # Append the integer to the n list
        s.m += 1       # Increment the count of distinct integers

    s.sub()


if __name__ == "__main__":
    main()
