import random


def UserDict():
    d = {}
    n = int(input("Enter total no. of values in dictionary: "))
    for i in range(n):
        k = random.randrange(0, 100)
        d[k] = input(f"Enter a value for key {k}: ")
    print("Dictionary:", d)

    tot_num = 0
    sum1 = 0
    final_str = ""
    special_char = []

    for value in d.values():
        if value.isdigit():
            sum1 += int(value)
            tot_num += 1
        elif isinstance(value, str):
            final_str += value
            if all(char in "!@#$%^&*()_+[]{}|;':,.<>?/~`" for char in value):
                special_char.append(value)

    if tot_num > 0:
        average = sum1 / tot_num
        print(f"Average: {average}")
    else:
        print("No numeric values to calculate the average.")

    print("Special characters:", special_char)
    print("Concatenated string:", final_str)
    search_value = input("Enter a value to search for: ")
    found_keys = [key for key, value in d.items() if value == search_value]
    if found_keys:
        print(f"Keys with value '{search_value}': {found_keys}")
    else:
        print(f"No keys found with value '{search_value}'")
    print("Values with only special characters:")
    for value in special_char:
        print(value)


def main():
    UserDict()


main()
