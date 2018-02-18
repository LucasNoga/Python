import os, sys

l = int(input())
h = int(input())
t = input()
alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
t = t.upper()

for i in range(h):
    row = input()
    resultat = ""
    print("t: " + t, file=sys.stderr)

    print(row[104:108], file=sys.stderr)
    for j in t:
        print("j: " + j, file=sys.stderr)
        if not j in alph:
            print("row 104-108: " + row[104:108], file=sys.stderr)
            resultat += row[104:108]
        else:
            po = alph.index(j)
            resultat += row[po * l:(po + 1) * l]
    print("resultat: " + resultat, file=sys.stderr)
    print(resultat)