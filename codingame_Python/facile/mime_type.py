import sys
import math

n = int(input())
q = int(input())
sorts={}
for i in range(n):
    ext, mt = input().split()
    sorts[ext.upper()]=mt

for k in range(q):
    fname = input()

    if '.' in fname:
        extensions=fname.split('.')[-1].upper()
    else:
        extensions=None

    if extensions in sorts.keys():
        for v in sorts:
            if v==extensions:
                print(sorts[v])
    else:
        print("UNKNOWN")