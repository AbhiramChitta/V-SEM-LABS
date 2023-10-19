import re
re_functions = dir(re)
find_functions = [func for func in re_functions if 'find' in func]
sorted_functions = sorted(find_functions)
for f in sorted_functions:
    print(f)
