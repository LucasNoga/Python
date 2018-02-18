import sys
import math

# The while loop represents the game.
# Each iteration represents a turn of the game
# where you are given inputs (the heights of the mountains)
# and where you have to print an output (the index of the mountain to fire on)
# The inputs you are given are automatically updated according to your last actions.


# game loop

while True:
    montagne_plus_haute = 0
    hauteur_montagne_plus_haute = 0
    for i in range(8):
        mountain_h = int(input())  # represents the height of one mountain.
        if hauteur_montagne_plus_haute < mountain_h:
            montagne_plus_haute = i
            hauteur_montagne_plus_haute = mountain_h

    # The index of the mountain to fire on.
    print(montagne_plus_haute)


# 2 eme méthode
while True:
    print(max([(int(input()), x) for x in range(8)])[1])