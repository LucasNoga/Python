import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

surface_n = int(input())  # the number of points used to draw the surface of Mars.$
for i in range(surface_n):
    # land_x: X coordinate of a surface point. (0 to 6999)
    # land_y: Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
    land_x, land_y = [int(j) for j in input().split()]

# game loop
while True:
    # h_speed: la vitesse vhorizontale en m/s peut etre negative.
    # v_speed: la vitesse verticale en m/s peut etre negative
    # fuel: la quantité de carburant restant en litre.
    # rotate: la rotation en degres (-90 to 90).
    # power: la puissance de la fusee (0 to 4).
    x, y, h_speed, v_speed, fuel, rotate, power = [int(i) for i in input().split()]
    puissance = 0
    hauteur = y

    # ralentissement de la fusee
    if v_speed <= -40:
        puissance = 4
    else:
        puissance = 0

    print(hauteur, file=sys.stderr)
    print("0 " + str(puissance))
