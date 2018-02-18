import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.
# ---
# Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.

# light_x: the X position of the light of power
# light_y: the Y position of the light of power
# initial_tx: Thor's starting X position
# initial_ty: Thor's starting Y position
light_x, light_y, initial_tx, initial_ty = [int(i) for i in input().split()]

thor_x = initial_tx
thor_y = initial_ty

# la direction que doit prendre thor

# game loop
while True:
    direction_verticale = ""
    direction_horizontale = ""
    remaining_turns = int(input())  # The remaining amount of turns Thor can move. Do not remove this line.

    if thor_y > light_y:
        thor_y += 1
        direction_verticale = "N"

    elif thor_y < light_y:
        thor_y += 1
        direction_verticale = "S"

    if thor_x > light_x:
        thor_x -= 1
        direction_horizontale = "W"

    elif thor_x < light_x:
        thor_x += 1
        direction_horizontale = "E"

    print(direction_verticale + direction_horizontale)
