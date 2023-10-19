f = open("f1.txt", "r")
l = []

# Split each line into words and store them in the list 'l'
for line in f:
    words = line.split()
    l.extend(words)  # Extend the list 'l' with the words from the current line

k = {}
for word in l:
    if word in k:
        k[word] += 1
    else:
        k[word] = 1

print(k)
