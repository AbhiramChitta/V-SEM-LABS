def calsq(x):
    return x ** 2


cache = {}


def square(x):
    if x in cache:
        return cache[x]
    else:
        result = calsq(x)
        cache[x] = result
        return result


print(square(3))
print(square(2))

