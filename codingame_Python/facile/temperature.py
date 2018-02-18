import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

n = int(input())  # the number of temperatures to analyse
temps = input()  # the n temperatures expressed as integers ranging from -273 to 5526

#on converti la liste en chaine
temps_tab = temps.split(" ")

if len(temps) == 0:
    print(0)
else:
    #conversion de la liste temps en une liste d'entier
    signe=False
    basse_temp = 10000

    temps_int = []
    for temperature in temps_tab:
        temp = int(temperature)
        temps_int.append(temp)

    for temperature in temps_int:
        if abs(temperature) < abs(basse_temp):
            basse_temp = temperature;
        elif abs(temperature) == abs(basse_temp):
            if temperature > basse_temp:
                basse_temp = temperature;
    print(basse_temp)


#2eme methode

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

n = int(input())  # the number of temperatures to analyse
temps = input()  # the n temperatures expressed as integers ranging from -273 to 5526

T = [int(s) for s in input().split()]
print(T and sorted(sorted(T,reverse=True),key=abs)[0] or 0)