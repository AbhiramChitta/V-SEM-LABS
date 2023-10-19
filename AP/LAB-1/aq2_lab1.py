num = int(input("Enter a number: "))
s = 0
temp = num
while temp > 0:
    digit = temp % 10
    s += digit ** 3
    temp //= 10

if num == s:
    print(num, "ARMSTRONG")
else:
    print(num, "NOT ARMSTRONG")
