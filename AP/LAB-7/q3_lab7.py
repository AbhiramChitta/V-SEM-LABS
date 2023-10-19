# Read the contents of the file and store each line in a list
with open("f1.txt", "r") as f:
    lines = [line.strip() for line in f]

# Reverse the order of lines
lines.reverse()

# Write the reversed lines back to the file
with open("f1.txt", "w") as f:
    for line in lines:
        f.write(line + "\n")
