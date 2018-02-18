import sys

n = int(input())
puissance_chevaux = list()
for i in range(n):
    pi = int(input())
    puissance_chevaux.append(pi)

puissance_chevaux.sort()  # trie le tableau
print(puissance_chevaux, sys.stderr)
plus_petit_ecart = 10000
for i, item in enumerate(puissance_chevaux):
    print("test1 : ", i, sys.stderr)
    print("test2 : ", item, sys.stderr)

    if i != len(puissance_chevaux) - 1:
        ecart = abs(puissance_chevaux[i] - puissance_chevaux[i + 1])
        print("écart : ", ecart, sys.stderr)
        if plus_petit_ecart > ecart:
            plus_petit_ecart = ecart
            print("plus_petit_écart : ", plus_petit_ecart, sys.stderr)
print(plus_petit_ecart)
