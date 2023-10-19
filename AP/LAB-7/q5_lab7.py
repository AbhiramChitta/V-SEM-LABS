import re
k = "red racing ca"
if re.match(r'^(.).*\1$', k):
    print("true")
else:
    print("false")
    