f = open("f1.txt", "r")
char = 0
lines = 0
words = 0
for line in f:
    lines += 1
    words += len(line.split())
    char += len(line)
print(lines)
print(words)
print(char)
