# coding=utf-8

import random

NB_LIGNES = 4

"""
lancement de la partie
"""


def jouer_partie():
    plateau = generer_jeu(9)
    afficher_tableau(plateau)
    afficher_etat(plateau)

    # sep()
    # print("affichage du tableau numérique\n")
    # afficher_tableau(tab3)

    # print("affichage de l'état\n")
    # afficher_etat(tab)

    # sep()

    # print("générer aléatoirement un état\n")


    # sep()

    # print("\nfaire une action sur tab enleve 2 allumettes de la 3eme ligne\n")
    # appliquer(tab, 2, 2)

    # sep()

    # print("\nchoix aléatoire d'une ligne\n")
    # choix_aleatoire_ligne(tab)

    # sep()

"""
un separateur
"""
def sep():
    print("\n********************************************************************************************************\n")

"""
affiche les valeurs numériques
"""

"""
genere aleatoirement un etat
"""
def generer_jeu(nb_allum):
    tab = creer_tableau()
    if nb_allum <= 0:
        print("ERREUR")
    else:
        for i in range(nb_allum):
            nbrand = random.randint(0, NB_LIGNES-1)  # faire un random
            tab[nbrand] += 1
            i += 1
    return tab

def creer_tableau():
    tab = []
    for i in range(NB_LIGNES):
        tab.append(0)
    return tab


def afficher_tableau(tableau):
    print("[ ", end='')
    for i in range(NB_LIGNES):
        print("{} ".format(tableau[i]), end='')
    print("]")


""" affiche les allumettes """
def afficher_etat(etat):
    j = 0
    i = 0
    print("______________\n")
    while i < NB_LIGNES:
        while j < etat[i]:
            print(" | ", end='')
            j += 1
        print("\n")
        j = 0
        i += 1
    print("______________\n")

def est_un_etat_final(etat):
    compteur = 0
    for i in NB_LIGNES:
        compteur += etat[i]
        i += 1
    if compteur <= 1:
        return 1
    else:
        return 0


def est_applicable(etat, ligne, nb_allum):
    if etat[ligne] >= nb_allum:
        if nb_allum == 0:
            return 0
        else:
            return 1
    else:
        return 0


def appliquer(etat, ligne, nb_allum):
    if est_applicable(etat, ligne, nb_allum):
        etat[ligne] -= nb_allum
    else:
        print("ERREUR")

    print("affichage numerique\n")
    afficher_tableau(etat)
    print("\naffichage etat\n")
    afficher_etat(etat)


def choix_aleatoire_ligne(etat):
    ligne_random = 0
    while etat[ligne_random] == 0:
        print("rechercher d'une autre ligne\n")
        ligne_random = random.randint(1, NB_LIGNES)
        print("la ligne est %d\n", ligne_random)
        print(" il y a {} allumettes\n", etat[ligne_random])  # tester avec le format
    print("une bonne ligne est donc %d\n", ligne_random)
    print("a la ligne %d il y a %d allumettes.", ligne_random, etat[ligne_random])
    return ligne_random

if __name__ == "__main__":
    # appele de la partie
    jouer_partie()

