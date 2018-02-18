Énoncé



Dans ce challenge, vous devez brancher des rallonges pour obtenir la plus grande longueur possible. Les rallonges peuvent avoir différents types : mâle-femelle, femelle-mâle, femelle-femelle, mâle-mâle. La rallonge ainsi assemblée doit obligatoirement avoir une prise mâle à une extrémité et une prise femelle à l'autre extrémité.



Format des données



Entrée

- Ligne 1 : un entier N compris entre 1 et 1000 représentant le nombre de rallonges.

- Lignes 2 à N+1 : une chaîne de 3 caractères et un entier compris entre 1 et 50 séparés par un espace. La chaîne correspond au type de prise : M-M, F-M, M-F ou F-F et l'entier correspond à sa longueur.



Sortie

Un entier représentant la longueur maximale obtenable en branchant des rallonges entre elles et en obtenant à la fin une rallonge avec une prise mâle à une extrémité et une prise femelle à l'autre extrémité.


#*****
#Solution by ISOGRAD
#*****

N = int(input())
lengths = {}
for _ in range(N):
    sex, length = input().split()
    lengths.setdefault(sex, []).append(int(length))
lengths['M-M'].sort()
lengths['F-F'].sort()
longest = sum(lengths['M-F']) + sum(lengths['F-M'])
nb_mm = len(lengths['M-M'])
nb_ff = len(lengths['F-F'])
if nb_mm <= nb_ff:
    longest += sum(lengths['M-M']) + sum(lengths['F-F'][-nb_mm:])
else:
    longest += sum(lengths['F-F']) + sum(lengths['M-M'][-nb_ff:])
print(longest)
