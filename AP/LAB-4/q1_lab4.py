import math

x = int(input("Enter number: "))
print(math.sin(x))
try:
    print(math.sqrt(x))
except ValueError as de:
    print("Cannot be negative")
try:
    print(math.log(x))
except ValueError as ve:
    print("-Infinite")

