# coding: utf-8

import os
import pickle
from random import choice
from donnees import *

# Fonctions gérant les éléments saisis par l'utilisateur
def recuperer_nom():
    nom = raw_input("Tapez votre nom : ")
    if not nom.isalnum() and len(nom) < 4:
        print("Ce nom est invalide.")
        return recuperer_nom()
    else:
        return nom

# Gestion des scores
def recuperer_scores():
    if os.path.exists(nom_fichier_scores):
        # On le récupère
        fichier_scores = open(nom_fichier_scores, "rb")
        mon_depickler = pickle.Unpickler(fichier_scores)
        scores = mon_depickler.load()
        fichier_scores.close()
    else: # Le fichier n'existe pas
        scores = {}
    return scores

# Fonctions gérant les éléments saisis par l'utilisateur
def recup_lettre():
    lettre = raw_input("Tapez une lettre: ")
    lettre = lettre.lower()
    if len(lettre) > 1 or not lettre.isalpha():
        print("Vous n'avez pas saisi une lettre valide.")
        return recup_lettre()
    else:
        return lettre

# Fonctions du jeu de pendu
def choisir_mot():
    return choice(liste_mots)

def recuperer_mot_masque(mot_complet, lettres_trouvees):
    mot_masque = ""
    for lettre in mot_complet:
        if lettre in lettres_trouvees:
            mot_masque += lettre
        else:
            mot_masque += "*"
    return mot_masque

# Enregistrement des scores
def enregistrer_scores(scores):
    fichier_scores = open(nom_fichier_scores, "wb") # On écrase les anciens scores
    mon_pickler = pickle.Pickler(fichier_scores)
    mon_pickler.dump(scores)
    fichier_scores.close()