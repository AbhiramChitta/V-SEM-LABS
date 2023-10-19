
row1 = int(input("Enter the number of rows in the first matrix:"))
column1 = int(input("Enter the number of columns in the first matrix:"))
row2 = int(input("Enter the number of rows in the second matrix:"))
column2 = int(input("Enter the number of columns in the second matrix:"))
dict1 = {}
dict2 = {}

for i in range(row1):
    for j in range(column1):
        element = int(input("Enter the elements row wise:"))
        if element != 0:
            dict1[i, j] = element

for i in range(row2):
    for j in range(column2):
        element = int(input("Enter the elements row wise:"))
        if element != 0:
            dict2[i, j] = element

rows = max(row1, row2)
columns = max(column1, column2)
result = [[0 for _ in range(columns)]for _ in range(rows)]
for i in range(rows):
    for j in range(columns):
        if (i, j) in dict1:
            result[i][j] += dict1[(i, j)]
        if (i, j) in dict2:
            result[i][j] += dict2[(i, j)]
print("Result matrix:")
for i in range(rows):
    for j in range(columns):
        print(result[i][j], end="\t")
    print()


