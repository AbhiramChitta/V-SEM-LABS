def is_hexadecimal(str2):
    return all(c.isdigit() or c in 'abcdef' for c in str2.lower())


str1 = input("Enter a string: ")
if is_hexadecimal(str1):
    print("HEXADECIMAL")
else:
    print("NOT HEXADECIMAL")
