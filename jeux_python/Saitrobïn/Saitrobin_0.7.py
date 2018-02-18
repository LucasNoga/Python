# coding: utf-8

# Saitrobïn_0.7.py
# POSADAS Valentin
# Update: bestiaire inséré dans un fichier txt, correction d'un bug dans l'inventaire
from random import *
import time

# ------------------------------------------------------------------------------#
# ------------------------------------------------------------------------------#
# ------------------------------CHARGEMENT--------------------------------------#
# ------------------------------------------------------------------------------#
# ------------------------------------------------------------------------------#

# chargement monstres
bestiaire = open("bestiaire.txt","r")
best_contenu = bestiaire.readlines()
tb_race = []
ingrédients = []
tb_att = []
tb_pv = []
tb_r_att = []
tb_r_pv = []
tb_exp = []
tb_gold = []
z = 0

# boucle permettant de supprimer les \n derrière les composants de la liste
while z < len(best_contenu):
    obj = best_contenu[z]
    fin = len(obj)-1
    tampon = obj[0:fin]
    best_contenu[z] = tampon
    z+=1
bestiaire.close()
# sépare les différentes stats des monstres
z = 0
while z < len(best_contenu):
    tb_race.append(str(best_contenu[z]))
    ingrédients.append(str(best_contenu[z+1]))
    tb_att.append(int(best_contenu[z+2]))
    tb_pv.append(int(best_contenu[z+3]))
    tb_r_att.append(float(best_contenu[z+4]))
    tb_r_pv.append(float(best_contenu[z+5]))
    tb_exp.append(int(best_contenu[z+6]))
    tb_gold.append(int(best_contenu[z+7]))
    z += 8


# chargement objets
inventaire = open("inventaire.txt","r")
inv_contenu = inventaire.readlines()
z = 0
# boucle permettant de supprimer les \n derrière les composants de la liste
while z < len(inv_contenu):
    obj = inv_contenu[z]
    fin = len(obj)-1
    tampon = obj[0:fin]
    inv_contenu[z] = tampon
    z+=1
inventaire.close()



# chargement classement
classement = open("classement.txt","r")
class_contenu = classement.readlines()
class_contenu_n = []
class_contenu_niv = []
class_contenu_c = []
class_contenu_t = []
z = 0

# boucle permettant de supprimer les \n derrière les composants de la liste
while z < len(class_contenu):
    obj = class_contenu[z]
    fin = len(obj)-1
    tampon = obj[0:fin]
    class_contenu[z] = tampon
    z+=1
classement.close()
# sépare les différentes catégories du classement
z = 0
while z < len(class_contenu):
    class_contenu_n.append(class_contenu[z])
    class_contenu_niv.append(class_contenu[z+1])
    class_contenu_c.append(class_contenu[z+2])
    class_contenu_t.append(class_contenu[z+3])
    z += 4



# ------------------------------------------------------------------------------#
# ------------------------------------------------------------------------------#
# ------------------------------VARIABLES---------------------------------------#
# ------------------------------------------------------------------------------#
# ------------------------------------------------------------------------------#



# variables
partie = False
temps = 0
rep = 0

# glace > foudre
# feu > glace
# foudre > feu
tb_s = ["feu", "foudre", "glace"]
tb_c = ["guerrier", "chasseur", "mage", "boloss"]
# stats du joueur
n = ""
c = 0
s = 0
pvmax = 130
pv = 130
bonuspv = 0
att = 10
bonusatt = 0
mag = 10
bonusmag = 0
niv = 1
exp = 0
gold = 0
butin = 0
diffi = 0
equipement = [-1, -1, -1, -1, "/", "/", "/", "/"]
stock = [-1, -1, -1, -1, -1, "/", "/", "/", "/", "/"]
nb_obj = (int(len(inv_contenu))//9)-1

# effets combat
stun = False
sommeil = False
incantation = False
transmutation = False
berzerk = False
annuler = False
fuite = False

# runes
rune = ["feu","foudre","glace","létal","bestial","anima"]
rune_text = ["de feu","de foudre","de glace","létale","bestiale","d'anima"]
rune_desc = ["Enchante votre arme de flammes craintes par les monstres de glace","Enchante votre arme d'éclairs craints par les monstres de feu","Enchante votre arme de glace crainte par les monstres de foudre","Cette rune vous octroie une chance de coup critique","Cette rune vous octroie une chance d'étourdir un ennemi","Cette rune enchante votre arme avec votre magie"]
rune_lvl = [0,0,0,0,0,0]
rune_xp = [0,0,0,[0,0],[0,0],[0,0]]
rune_act = -1

#sorts
sort = ["anima","narcose","berzerk","transmutation","incantation"]
sort_desc = ["Envoie une explosion de magie non élémentaire","Un sort pouvant endormir l'adversaire","Une rage incontrôlable parcourant votre corps, augmentant votre force pour le combat","Un sort pouvant transformer un monstre en une montagne d'or","Un sort qui, une fois canalisé, tuera à coup sûr l'adversaire"] 
mana = [-1,-1,-1,-1,-1]

#interrupteur quêtes
quete_1 = False
quete_2 = False
ch_type = ""
ch_nb = 0
ch_nbmax = 0
quete_3 = False
quete_4 = False
quete_5 = False

#interrupteur loose
loose = False

#------------------------------------------------------------------------------#
#------------------------------------------------------------------------------#
#------------------------------FONCTIONS---------------------------------------#
#------------------------------------------------------------------------------#
#------------------------------------------------------------------------------#


#génère aléatoirement des monstres
def monstre():
    global n,niv,diffi,tb_s,tb_race,tb_att,tb_pv,_tb_r_att,tb_r_pv,tb_exp,tb_gold
    race = randint(0,4)
    niv_m = randint(niv+diffi,niv+diffi+2)
    s_m = randint(0,2)
    return [niv_m,tb_race[race],tb_s[s_m],int(tb_att[race]+niv_m*tb_r_att[race]),int(tb_pv[race]+niv_m*tb_r_pv[race]),tb_exp[race]+randint(0,5),tb_gold[race]+randint(0,5),""]


#gestion d'expérience et de prise de niveau
def xp(experience):
    global exp, pvmax, c, pv, att, mag, niv
    exp = exp + experience
    if exp >= 100:
        print("Vous avez gagné un niveau!")
        time.sleep(1.5)
        exp = exp - 100
        niv = niv + 1
        if c == 0:
            pvmax = pvmax + 10 + randint(0,5)
            pv = pv + 10
            att = att + 2 + randint(0,2)
            mag = mag + randint(0,1)
        if c == 1:
            pvmax = pvmax + 6 + randint(0,2)
            pv = pv + 6
            att = att + 3 + randint(0,3)
            mag = mag + 1 + randint(0,2)
        if c == 2:
            pvmax = pvmax + 7 + randint(0,4)
            pv = pv + 7
            att = att + 1 + randint(0,2)
            mag = mag + 3 + randint(0,3)
        if c == 3:
            pvmax = pvmax + 7 + randint(0,3)
            pv = pv + 7
            att = att + 2 + randint(0,3)
            mag = mag + 1 + randint(0,2)  


#gère le level up des runes
def rune_lvlup(race,elem):
    global rune_act,rune_lvl,rune_text,rune_xp,tb_race
    if rune_act == 0:
        if elem == "feu":
            if rune_lvl[rune_act] < 4:
                print("Votre rune ",rune_text[rune_act]," a absorbé l'âme du monstre!")
                rune_xp[rune_act] += 1
                if rune_xp[rune_act] == 10:
                    print("Votre rune a augmenté en puissance!")
                    rune_lvl[rune_act] += 1
                    rune_xp[rune_act] = 0
    elif rune_act == 1:
        if elem == "foudre":
            if rune_lvl[rune_act] < 4:
                print("Votre rune ",rune_text[rune_act]," a absorbé l'âme du monstre!")
                rune_xp[rune_act] += 1
                if rune_xp[rune_act] == 10:
                    print("Votre rune a augmenté en puissance!")
                    rune_lvl[rune_act] += 1
                    rune_xp[rune_act] = 0
    elif rune_act == 2:
        if elem == "glace":
            if rune_lvl[rune_act] < 4:
                print("Votre rune ",rune_text[rune_act]," a absorbé l'âme du monstre!")
                rune_xp[rune_act] += 1
                if rune_xp[rune_act] == 10:
                    print("Votre rune a augmenté en puissance!")
                    rune_lvl[rune_act] += 1
                    rune_xp[rune_act] = 0
    elif rune_act == 3:
        if race == tb_race[1]:
            if rune_lvl[rune_act] < 4:
                print("Votre rune ",rune_text[rune_act]," a absorbé l'âme du monstre!")
                tb_temp = rune_xp[rune_act]
                tb_temp[0] += 1
                rune_xp[rune_act] = tb_temp
                if rune_xp[rune_act] == [5,5]:
                    print("Votre rune a augmenté en puissance!")
                    rune_lvl[rune_act] += 1
                    rune_xp[rune_act] = [0,0]
        elif race == tb_race[4]:
            if rune_lvl[rune_act] < 4:
                print("Votre rune ",rune_text[rune_act]," a absorbé l'âme du monstre!")
                tb_temp = rune_xp[rune_act]
                tb_temp[1] += 1
                rune_xp[rune_act] = tb_temp
                if rune_xp[rune_act] == [5,5]:
                    print("Votre rune a augmenté en puissance!")
                    rune_lvl[rune_act] += 1
                    rune_xp[rune_act] = [0,0]
    elif rune_act == 4:
        if race == tb_race[3]:
            if rune_lvl[rune_act] < 4:
                print("Votre rune ",rune_text[rune_act]," a absorbé l'âme du monstre!")
                tb_temp = rune_xp[rune_act]
                tb_temp[0] += 1
                rune_xp[rune_act] = tb_temp
                if rune_xp[rune_act] == [5,5]:
                    print("Votre rune a augmenté en puissance!")
                    rune_lvl[rune_act] += 1
                    rune_xp[rune_act] = [0,0]
        elif race == tb_race[5]:
            if rune_lvl[rune_act] < 4:
                print("Votre rune ",rune_text[rune_act]," a absorbé l'âme du monstre!")
                tb_temp = rune_xp[rune_act]
                tb_temp[1] += 1
                rune_xp[rune_act] = tb_temp
                if rune_xp[rune_act] == [5,5]:
                    print("Votre rune a augmenté en puissance!")
                    rune_lvl[rune_act] += 1
                    rune_xp[rune_act] = [0,0]
    elif rune_act == 5:
        if race == tb_race[0]:
            if rune_lvl[rune_act] < 4:
                print("Votre rune ",rune_text[rune_act]," a absorbé l'âme du monstre!")
                tb_temp = rune_xp[rune_act]
                tb_temp[0] += 1
                rune_xp[rune_act] = tb_temp
                if rune_xp[rune_act] == [5,5]:
                    print("Votre rune a augmenté en puissance!")
                    rune_lvl[rune_act] += 1
                    rune_xp[rune_act] = [0,0]
        elif race == tb_race[2]:
            if rune_lvl[rune_act] < 4:
                print("Votre rune ",rune_text[rune_act]," a absorbé l'âme du monstre!")
                tb_temp = rune_xp[rune_act]
                tb_temp[1] += 1
                rune_xp[rune_act] = tb_temp
                if rune_xp[rune_act] == [5,5]:
                    print("Votre rune a augmenté en puissance!")
                    rune_lvl[rune_act] += 1
                    rune_xp[rune_act] = [0,0]


#gère la chasse de monstre selon la quête activée
def chasse(typ,elem):
    global ch_nb,ch_nbmax,ch_type,quete_1,quete_2
    if quete_1 == True:
        if ch_type == typ:
            time.sleep(0.2)
            print("Vous avez récolté l'ingrédient sur le ",typ)
            ch_nb = ch_nb - 1
            if ch_nb == 0:
                quete()
    elif quete_2 == True:
        if ch_type == elem:
            time.sleep(0.2)
            print("Vous avez récolté l'âme de ",elem," sur le ",typ)
            ch_nb = ch_nb - 1
            if ch_nb == 0:
                quete()
    
#soin
def soin():
    global pv
    global pvmax
    if pvmax >= pv + 20 + 3*niv:
        pv = pv +20 + 3*niv
    else:
        pv = pvmax


#ajout d'un objet dans l'inventaire et vérifie si il y a assez de place dans l'inventaire
def ajout_obj(id):
    global stock, inv_contenu
    z = 0
    place = False
    while z < 4 and place == False:
        if stock[z] != -1:
            z+=1
        else:
            place = True
    if place == True:
        stock[z] = int(id)
        stock[z+5] = str(inv_contenu[int(id)*9+1])
    else:
        print("Il n'y a pas assez de place dans l'inventaire!")
        print("Voulez vous retirer un objet de votre inventaire?")
        act01 = input("(o)ui - (n)on : ")
        time.sleep(0.3)
        if act01 == "o":
            print("1: ",stock[5])
            print("2: ",stock[6])
            print("3: ",stock[7])
            print("4: ",stock[8])
            print("5: ",stock[9])
            print("")
            print("6: ",inv_contenu[int(id)*9+1])
            act02 = input("Lequel? (1,2,3,4,5,6) ")
            if act02 == "1" or act02 == "2" or act02 == "3" or act02 == "4" or act02 == "5":
                act02 = int(act02)
                stock[act02-1] = int(id)
                stock[act02+4] = str(inv_contenu[int(id)*9+1])


#génère les dégâts causés par une attaque en fonction de la rune équipée
def degats(elem):
    global att,mag,rune_act,rune_lvl,stun
    stun = False
    if rune_act == 0:
        if elem == "glace":
            print("La rune est efficace!")
            return (att + int(randint(0,2)*niv*0.5))*(1.25+(0.25*rune_lvl[rune_act]))
        elif elem == "foudre":
            print("La rune n'est pas très efficace...")
            return (att + int(randint(0,2)*niv*0.5))*(0.70+(0.05*rune_lvl[rune_act]))
        else:
            return att + int(randint(0,2)*niv*0.5)
    elif rune_act == 1:
        if elem == "feu":
            print("La rune est efficace!")
            return (att + int(randint(0,2)*niv*0.5))*(1.25+(0.25*rune_lvl[rune_act]))
        elif elem == "glace":
            print("La rune n'est pas très efficace...")
            return (att + int(randint(0,2)*niv*0.5))*(0.70+(0.05*rune_lvl[rune_act]))
        else:
            return att + int(randint(0,2)*niv*0.5)
    elif rune_act == 2:
        if elem == "foudre":
            print("La rune est efficace!")
            return (att + int(randint(0,2)*niv*0.5))*(1.25+(0.25*rune_lvl[rune_act]))
        elif elem == "feu":
            print("La rune n'est pas très efficace...")
            return (att + int(randint(0,2)*niv*0.5))*(0.70+(0.05*rune_lvl[rune_act]))
        else:
            return att + int(randint(0,2)*niv*0.5)
    elif rune_act == 3:
        rand = randint(1,100)
        if rand >= (82.5-7.5*rune_lvl[rune_act]):
            print("Coup critique!")
            return (att + int(randint(0,2)*niv*0.5))*(1.6+(0.1*rune_lvl[rune_act]))
        else:
            return att + int(randint(0,2)*niv*0.5)
    elif rune_act == 4:
        rand = randint(1,100)
        if rand >= (82.5-7.5*rune_lvl[rune_act]):
            print("Un coup puissant!")
            stun = True
            return (att + int(randint(0,2)*niv*0.5))*(1.3+(0.05*rune_lvl[rune_act]))
        else:
            return att + int(randint(0,2)*niv*0.5)
    elif rune_act == 5:
        rand = randint(1,100)
        if rand >= (85-10*rune_lvl[rune_act]):
            print("De la magie émane de votre coup!")
            return att*0.70 + mag*(0.60+(0.10*rune_lvl[rune_act])) + int(randint(0,2)*niv*0.5)
        else:
            return att + int(randint(0,2)*niv*0.5)
    else:
        return att + int(randint(0,2)*niv*0.5)


#génère les dégâts/effets suivant le sort utilisé
def sorts(elem):        
    global n,c,niv,gold,sort,mana,mag,att,pv,pvmax,sommeil,stun,tb_s,s,annuler,berzerk,transmutation,incantation
    if mana[0] == -1 and mana[1] == -1 and mana[1] == -1 and mana[1] == -1 and mana[1] == -1:
        print("Vous lancez une boule de ",tb_s[s],"!")
        time.sleep(1)
        multi = 1
        if elem == "feu":
            if s == 1:
                print("C'est très efficace!")
                multi = 2
            elif s == 2:
                print("Ce n'est pas très efficace...")
                multi = 0.5
        elif elem == "foudre":
            if s == 0:
                print("Ce n'est pas très efficace...")
                multi = 0.5
            elif s == 2:
                print("C'est très efficace!")
                multi = 2
        elif elem == "glace":
            if s == 0:
                print("C'est très efficace!")
                multi = 2
            elif s == 1:
                print("Ce n'est pas très efficace...")
                multi = 0.5
        print("Vous infligez ",int(mag * 2.5 *multi)," points de dégâts!")
        return mag * 2.5 *multi
    else:
        inter = False
        print("1 - boule de ",tb_s[s],"   mana: /")
        z = 2
        while z < len(rune)+1:
            if mana[z-2] != -1:
                print(z," - ",sort[z-2],"   mana: ",mana[z-2])
            z += 1
        while inter == False:
            act = input("Quel sort? (1,2,3...,(a)nnuler) ")
            if act == "1":
                print("Vous lancez une boule de ",tb_s[s],"!")
                time.sleep(1)
                multi = 1
                if elem == "feu":
                    if s == 1:
                        print("C'est très efficace!")
                        multi = 2
                    elif s == 2:
                        print("Ce n'est pas très efficace...")
                        multi = 0.5
                elif elem == "foudre":
                    if s == 0:
                        print("Ce n'est pas très efficace...")
                        multi = 0.5
                    elif s == 2:
                        print("C'est très efficace!")
                        multi = 2
                elif elem == "glace":
                    if s == 0:
                        print("C'est très efficace!")
                        multi = 2
                    elif s == 1:
                        print("Ce n'est pas très efficace...")
                        multi = 0.5
                print("Vous infligez ",int(mag * 2.5 *multi)," points de dégâts!")
                return mag * 2.5 *multi
            if act == "2":
                act = int(act)
                if mana[act-2] != -1:
                    if mana[act-2] != 0:
                        mana[act-2] = mana[act-2] - 1
                        print("Vous lancez une explosion d'anima!")
                        time.sleep(1)
                        print("Vous infligez ",int(mag * 2.75)," points de dégâts!")
                        return mag * 2.75
                    else:
                        print("Vous n'avez pas assez de mana!")
                else:
                    print("Veuillez sélectionner un sort disponible!")
            if act == "3":
                act = int(act)
                if mana[act-2] != -1:
                    if mana[act-2] != 0:
                        mana[act-2] = mana[act-2] - 1
                        rand = randint(1,100)
                        print("Vous tentez de l'endormir...")
                        time.sleep(1)
                        if rand >= (50 - 0.2*mag):
                            print("Vous avez réussi!")
                            sommeil = True
                            return 0
                        else:
                            return 0
                    else:
                        print("Vous n'avez pas assez de mana!")
                else:
                    print("Veuillez sélectionner un sort disponible!")
            if act == "4":
                act = int(act)
                if mana[act-2] != -1:
                    if mana[act-2] != 0:
                        mana[act-2] = mana[act-2] - 1
                        time.sleep(1)
                        print("Une soudaine rage parcourt votre corps!")
                        berzerk = True
                        return 0
                    else:
                        print("Vous n'avez pas assez de mana!")
                else:
                    print("Veuillez sélectionner un sort disponible!")
            if act == "5":
                act = int(act)
                if mana[act-2] != -1:
                    if mana[act-2] != 0:
                        mana[act-2] = mana[act-2] - 1
                        rand = randint(1,100)
                        print("Vous tentez de le transformer en or...")
                        time.sleep(1)
                        if rand >= (70 - 0.075*mag):
                            print("Vous avez réussi!")
                            transmutation = True
                            return 0
                        else:
                            return 0
                    else:
                        print("Vous n'avez pas assez de mana!")
                else:
                    print("Veuillez sélectionner un sort disponible!")
            if act == "6":
                act = int(act)
                if mana[act-2] != -1:
                    if mana[act-2] != 0:
                        mana[act-2] = mana[act-2] - 1
                        print("Vous commencez le rituel...")
                        time.sleep(1)
                        incantation = True
                        return 0
                    else:
                        print("Vous n'avez pas assez de mana!")
                else:
                    print("Veuillez sélectionner un sort disponible!")
            if act == "a":
                annuler = True
                return 0
            

#------------------------------------------------------------------------------#        
#------------------------------------------------------------------------------#
#----------------------------Evènement-----------------------------------------#
#------------------------------------------------------------------------------#
#------------------------------------------------------------------------------#
                

#génère un combat
def combat(tb_m):
    print("")
    global n,c,niv,exp,s,pv,pvmax,att,mag,loose,tb_s,gold,rune_act,stun,annuler,transmutation,berzerk,sommeil,incantation,fuite
    win = False
    print("C'est un ",tb_m[1]," de ",tb_m[2]," de niveau ",tb_m[0],"!")
    while win == False:
        r = input("Que faire? (a)ttaquer - (l)ancer un sort - (f)uir : ")
        if r == "a":
            print("Vous engagez le combat!")
            while tb_m[4] >= 0:
                print("")
                print("Le combat est intense...")
                time.sleep(0.3)
                a_temp = int(degats(tb_m[2]))
                if berzerk == True:
                    a_temp = int(a_temp*1.5)
                tb_m[4] = tb_m[4] - a_temp
                print("Vous infligez ",a_temp," points de dégâts au ",tb_m[1])
                if stun == True:
                    print(tb_m[1]," est étourdi!")
                    stun = False
                if sommeil == True:
                    rand = randint(1,100)
                    if rand >= (50 - 0.1*mag):
                        print(tb_m[1]," est endormi...")
                    else:
                        print("Il se réveille!")
                        sommeil = False
                        pv = pv - tb_m[3]
                        print(tb_m[1]," vous inflige ",tb_m[3]," points de dégâts")
                else:
                    pv = pv - tb_m[3]
                    print(tb_m[1]," vous inflige ",tb_m[3]," points de dégâts")
                time.sleep(1)
                if pv <= 0:
                    tb_m[4] = -1
                    print("Vous avez été vaincu!")
                    time.sleep(0.7)
                    win = True
                    loose = True
            if loose == False:
                sommeil = False
                berzerk = False
                print("")
                print("Vous avez remporté le combat!")
                time.sleep(1)
                rune_lvlup(tb_m[1],tb_m[2])
                print("Vous avez gagné ",tb_m[5]," points d'exp")
                xp(tb_m[5])
                print("Vous avez gagné ",tb_m[6]," pièces d'or")
                gold = gold + tb_m[6]
                chasse(tb_m[1],tb_m[2])
                win = True
        elif r == "l":
            a_temp = int(sorts(tb_m[2]))
            tb_m[4] = tb_m[4] - a_temp
            if tb_m[4] <= 0:
                sommeil = False
                berzerk = False
                print("Vous avez explosé ",tb_m[1],"!")
                time.sleep(1)
                rune_lvlup(tb_m[1],tb_m[2])
                print("Vous avez gagné ",tb_m[5]," points d'exp")
                xp(tb_m[5])
                print("Vous avez gagné ",tb_m[6]," pièces d'or")
                gold = gold + tb_m[6]
                chasse(tb_m[1],tb_m[2])
                win = True
            elif annuler == True:
                annuler = False
            elif transmutation == True:
                sommeil = False
                berzerk = False
                time.sleep(1)
                print("Vous avez transformé ",tb_m[1],"or!")
                time.sleep(1)
                print("Vous avez gagné ",tb_m[6]*4," pièces d'or")
                gold = gold + tb_m[6]*4
                win = True
                transmutation = False
            elif incantation == True:
                inc = False
                z = 0
                while inc == False:
                    time.sleep(0.5)
                    rand = randint(1,100)
                    if rand >= (75 - 0.25*mag - z * 17.5):
                        print("Le rituel est prêt!")
                        time.sleep(0.5)
                        sommeil = False
                        berzerk = False
                        print("Vous avez annihilé ",tb_m[1],"!")
                        time.sleep(1)
                        rune_lvlup(tb_m[1],tb_m[2])
                        print("Vous avez gagné ",tb_m[5]," points d'exp")
                        xp(tb_m[5])
                        print("Vous avez gagné ",tb_m[6]," pièces d'or")
                        gold = gold + tb_m[6]
                        chasse(tb_m[1],tb_m[2])
                        inc = True
                        win = True
                    else:
                        z += 1
                        print("Le rituel est pratiquement prêt...")
                        print(tb_m[1]," attaque!")
                        pv = pv - tb_m[3]
                        print(tb_m[1]," vous inflige ",tb_m[3]," points de dégâts")
                        if pv <= 0:
                            print("Vous avez été vaincu!")
                            time.sleep(1)
                            inc = True
                            win = True
                            loose = True
                
                incantation = False
            elif berzerk == True:
                time.sleep(0.5)
                print(tb_m[1]," attaque!")
                pv = pv - tb_m[3]*2
                print(tb_m[1]," vous inflige ",tb_m[3]*2," points de dégâts")
                if pv <= 0:
                    print("Vous avez été vaincu!")
                    time.sleep(1)
                    win = True
                    loose = True
            elif sommeil == True:
                print(tb_m[1]," est endormi...")
            
            
            else:
                print(tb_m[1]," a résisté...")
                time.sleep(0.5)
                print("Il riposte!")
                pv = pv - tb_m[3]*4
                print(tb_m[1]," vous inflige ",tb_m[3]*4," points de dégâts")
                if pv <= 0:
                    print("Vous avez été vaincu!")
                    time.sleep(1)
                    win = True
                    loose = True
        elif r == "f":
            if gold < 50:
                print("Vous ne pouvez pas fuir!")
            else:
                print("Vous tentez de fuir!")
                gold = gold - 30 + randint(0,20)
                if randint(0,1) == 1:
                    sommeil = False
                    berzerk = False
                    print("Vous réussissez à vous enfuir!")
                    fuite = True
                    win = True
                else:
                    print("Vous n'avez pas réussi à fuir!")


#événement coffre
def coffre():
    global n,c,niv,exp,s,pv,pvmax,att,mag,loose,tbs,gold,rune_lvl,rune_text,rune_act,butin,sort,mana
    cof = randint(1,100)
    if 1 <= cof <= 5:
        print("Il y a un monstre!")
        time.sleep(0.5)
        combat(monstre())
    else:
        cof2 = randint(1,100)
        if 1 <= cof2 <= 25:
            cof3 = randint(1,100)
            if 1 <= cof3 <= 33:
                print("Vous obtenez une potion de force!")
                time.sleep(0.5)
                print("Vous buvez la potion...")
                time.sleep(0.75)
                att = att + 5
            elif 34 <= cof3 <= 66:
                print("Vous obtenez une potion de puissance!")
                time.sleep(0.5)
                print("Vous buvez la potion...")
                time.sleep(0.75)
                mag = mag + 5
            elif 67 <= cof3 <= 100:
                print("Vous obtenez une potion de vie!")
                time.sleep(0.5)
                print("Vous buvez la potion...")
                time.sleep(0.75)
                pvmax = pvmax + 10
                pv = pv + 10
        elif 26 <= cof2 <= 45:
            temp01 = randint(0,nb_obj)
            print("Vous obtenez un(e) ",inv_contenu[temp01*9+1],"!")
            time.sleep(0.5)
            ajout_obj(temp01)
        elif 45 <= cof2 <= 60:
            cof3 = randint(1,100)
            if 1 <= cof3 <= 50:
                rand = randint(0,5)
                print("Incroyable, une rune ",rune_text[rand],"!")
                if rune_lvl[rand] != 0:
                    print("Vous en possédez déjà une. Elle est ajoutée à votre butin")
                    butin += 500
                else:
                    rune_lvl[rand] = 1
            elif 51 <= cof3 <= 100:
                rand = randint(0,5)
                print("Incroyable, un livre de magie!")
                print("Il permet d'apprendre ",sort[rand],".")
                if rune_lvl[rand] != 0:
                    print("Vous connaissez déjà ce sort. Le livre est ajouté à votre butin")
                    butin += 500
                else:
                    mana[rand] = 4
        elif 61 <= cof2 <= 100:
            print("Un trésor!")
            time.sleep(0.5)
            goldus = 100 + randint(0,200)
            print("Vous avez gagné ",goldus," pièces d'or")
            gold = gold + goldus

#événement quête
#la fonction génère une quête si aucune n'est en cours, ou enclencher le dénouement de la quête si il y en a une en cours
def quete():
    global quete_1,quete_2,quete_3,quete_4,quete_5,tb_race,ch_type,ch_nb,ch_nbmax,ingrédients,tb_s,att,mag,pv,pvmax,gold,rune_text,rune_lvl,niv,diffi,sort,mana,butin,nb_obj,inv_contenu    

    #sous fonction utile pour la 5ème quête
    def butin_quete(multi):
        z = 0
        while z < multi:
            rand = randint(0,3)
            if rand == 1 or rand == 2:
                rand2 = randint(0,nb_obj)
                print("Vous obtenez un ",inv_contenu[rand2*9+1],"!")
                ajout_obj(rand2)
                time.sleep(0.25)
            if rand == 3:
                rand2 = randint(0,5)
                print("Vous obtenez un livre de magie!")
                print("Il permet d'apprendre ",sort[rand2],".")
                if mana[rand2] != -1:
                    print("Vous connaissez déjà ce sort. Le livre est ajouté à votre butin")
                    butin += 500
                else:
                    mana[rand2] = 4
            if rand == 0:
                rand2 = randint(0,5)
                print("Vous obtenez une rune ",rune_text[rand2],"!")
                if rune_lvl[rand2] != 0:
                    print("Vous en possédez déjà une. Elle est ajoutée à votre butin")
                    butin += 500
                else:
                    rune_lvl[rand2] = 1
            tamp = 50 + randint(0,20)    
            print("Vous avez gagné ",tamp," pièces d'or")
            gold = gold + tamp
            z += 1
        time.sleep(0.25)
        
    act = ""
    if quete_1 == False and quete_2 == False and quete_3 == False and quete_4 == False and quete_5 == False:
        print("Il y a quelqu'un au fond de la pièce...")
        time.sleep(0.5)
        print("Cette personne s'approche de vous!")
        time.sleep(0.3)
        rand0 = randint(1,100)
        if 1 <= rand0 <= 20:
            print("Bonjour aventurier! Je suis un alchimiste à le recherche de certains ingrédients pour mes concoctions.")
            time.sleep(0.25)
            print("Malheureusement, j'ai sous estimé les monstres de ce donjon et je peine à récolter mes ingrédients.")
            time.sleep(0.25)
            print("Pourriez-vous m'aider à ma recherche d'ingrédients? Je vous ferai goûter une de mes potions!")
            while act != "o" and act != "n":
                act = input("Aider l'alchimiste? (o)ui - (n)on : ")
                if act == "o":
                    quete_1 = True
                    time.sleep(0.2)
                    print("Merci beaucoup! Je vais vous suivre jusqu'à ce que l'on trouve tout ce qu'il me faut.")
                    time.sleep(0.25)
                    rand = randint(0,len(tb_race)-1)
                    rand2 = randint(3,6)
                    print("Alors... J'ai besoin de ",rand2," ",ingrédients[rand],"!")
                    ch_type = tb_race[rand]
                    ch_nb = ch_nb + rand2
                    ch_nbmax = ch_nbmax + rand2
                    time.sleep(0.25)
                    print("Eh bien... C'est parti! Je vous suis!")
                    time.sleep(0.25)
                elif act == "n":
                    time.sleep(0.2)
                    print("Oh... D'accord.")
            return
        elif 21 <= rand0 <= 40:
            print("Bonjour voyageur! Je chasse les monstres de ce donjon pour récolter leur âme afin de créer des runes.")
            time.sleep(0.25)
            print("Je commence à être exténué de tous ces combats, de l'aide serait bien appréciable.")
            time.sleep(0.25)
            print("Est-ce que cela vous intéresserait-il de m'aider? Je pourrais vous donner une de mes runes.")
            while act != "o" and act != "n":
                act = input("Aider l'érudit? (o)ui - (n)on : ")
                if act == "o":
                    quete_2 = True
                    time.sleep(0.2)
                    print("Merci. Je vais vous suivre à partir de maintenant.")
                    time.sleep(0.25)
                    rand = randint(0,len(tb_s)-1)
                    rand2 = randint(3,6)
                    print("Il me faut encore ",rand2," âmes de ",tb_s[rand],".")
                    ch_type = tb_race[rand]
                    ch_nb = ch_nb + rand2
                    ch_nbmax = ch_nbmax + rand2
                    time.sleep(0.25)
                    print("Après vous!")
                    time.sleep(0.25)
                elif act == "n":
                    time.sleep(0.2)
                    print("...Très bien. Je comprends.")
            return
        elif 41 <= rand0 <= 60:
            print("Vous! Suivez-moi, j'ai besoin d'aide, je suis à la chasse d'un puissant démon qui se réfugie dans ce donjon.")
            time.sleep(0.25)
            print("Cela fait plusieurs jours que je le traque... Bon, qu'attendez-vous? Venez!")
            time.sleep(0.25)
            print("... Vous hésitez vraiment à m'aider? Bon... Je vous offrirai un de mes livres de magie!")
            while act != "o" and act != "n":
                act = input("Aider l'exorciste? (o)ui - (n)on : ")
                if act == "o":
                    quete_3 = True
                    time.sleep(0.2)
                    print("En avant! Il est parti là bas!")
                    time.sleep(0.25)
                elif act == "n":
                    time.sleep(0.2)
                    print("Comment osez-vous? Je n'ai pas de temps à perdre avec vous.")
        elif 61 <= rand0 <= 80:
            print("Oh, un aventurier! S'il vous plait, j'ai besoin d'aide!")
            time.sleep(0.25)
            print("Je suis un simple marchand, mais un voleur m'a dérobé ma rune de protection qui me protège des monstres!")
            time.sleep(0.25)
            print("Est-ce que vous pouvez m'aider? Je vous récompenserai grassement!")
            while act != "o" and act != "n":
                act = input("Aider le marchand? (o)ui - (n)on : ")
                if act == "o":
                    quete_4 = True
                    time.sleep(0.2)
                    print("Oh! Merci infiniement!")
                    time.sleep(0.25)
                    print("Je vous suis.")
                    time.sleep(0.25)
                elif act == "n":
                    time.sleep(0.2)
                    print("Olalah, comment vais-je faire?")
            return
        elif 81 <= rand0 <= 100:
            print("Bien le bonjour, compagnon! Je suis un chasseur de trésor!")
            time.sleep(0.25)
            print("J'ai entendu parler d'un butin incroyable dans ce donjon, mais j'ai du mal à progresser de pièce en pièce...")
            time.sleep(0.25)
            print("Pourriez-vous m'aider? On pourrait faire 50/50 sur le trésor!")
            while act != "o" and act != "n":
                act = input("Aider le chasseur de trésor? (o)ui - (n)on : ")
                if act == "o":
                    quete_5 = True
                    time.sleep(0.2)
                    print("Magnifique!")
                    time.sleep(0.25)
                    print("Je vous suis.")
                    time.sleep(0.25)
                elif act == "n":
                    time.sleep(0.2)
                    print("Oh bon, d'accord.")
            return


        
    elif quete_1 == True:
        if ch_nb == 0:
            print("")
            print("Alchimiste: Eh bien, c'était le dernier ingrédient qu'il me fallait!")
            time.sleep(0.25)
            print("Merci beaucoup pour votre aide! J'ai sur moi quelques potions permettant")
            print("de renforcer les caractéristiques naturelles! Laquelle voulez-vous?")
            time.sleep(0.25)
            while act != "v" and act != "f" and act != "p":
                act = input("potion de (v)ie - potion de (f)orce - potion de (p)uissance : ")
                if act == "v":
                    print("Vous buvez la potion de vie...")
                    time.sleep(0.5)
                    pvmax = pvmax + 10
                    pv = pv +10
                elif act == "f":
                    print("Vous buvez la potion de force...")
                    time.sleep(0.5)
                    att = att + 5
                elif act == "p":
                    print("Vous buvez la potion de puissance...")
                    time.sleep(0.5)
                    mag = mag + 5
            print("Je vous laisse ici! Je n'ai plus besoin rester ici maintenant. Au revoir!")
            time.sleep(1)
            print("")
            print("Quête accomplie!")
            print("Vous avez gagné ",ch_nbmax*15," points d'exp")
            xp(ch_nbmax*15)
            tamp = ch_nbmax*25+randint(5,25)
            print("Vous avez gagné ",tamp," pièces d'or")
            gold = gold + tamp
            quete_1 = False
        else:
            event()
            return
        return

    
    elif quete_2 == True:
        if ch_nb == 0:
            print("")
            print("Erudit: Parfait, c'était la dernière âme qu'il me fallait!")
            time.sleep(0.25)
            print("Encore merci pour votre aide, je ne m'en serai pas sorti sans vous!")
            print("Tenez, j'ai une rune pour vous.")
            time.sleep(0.25)
            rand = randint(0,5)
            print("Vous obtenez une rune ",rune_text[rand],"!")
            if rune_lvl[rand] != 0:
                print("Vous en possédez déjà une. Elle est ajoutée à votre butin")
                butin += 500
            else:
                rune_lvl[rand] = 1
            print("Adieu aventurier.")
            time.sleep(1)
            print("")
            print("Quête accomplie!")
            print("Vous avez gagné ",ch_nbmax*15," points d'exp")
            xp(ch_nbmax*15)
            tamp = ch_nbmax*25+randint(5,25)
            print("Vous avez gagné ",tamp," pièces d'or")
            gold = gold + tamp
            quete_2 = False
        else:
            event()
            return
        return

    
    elif quete_3 == True:
        print("Exorciste: Le voici! C'est le démon que je pourchasse!")
        time.sleep(0.25)
        print("J'espère que vous êtes prêt, j'ai besoin de canaliser mon énergie pour le capturer.")
        time.sleep(0.25)
        print("Je ne pourrais donc pas vous aider pour l'affronter!")
        time.sleep(0.5)
        combat([niv+diffi+3,"Démon",tb_s[randint(0,2)],int(7+2*(niv+diffi+3)),int(14+2*(niv+diffi+3)),40,50])
        if fuite == True:
            time.sleep(1)
            print("")
            print("Vous me laissez tout seul avec lui?!")
            time.sleep(0.25)
            print("Je vous maudis, vous et vos descendants!!")
            time.sleep(1)
            print("")
            print("Quête échouée!")
            quete_3 = False
            return
        else:
            time.sleep(1)
            print("")
            print("C'est pas trop tôt, vous l'avez enfin maîtrisé! Je le capture.")
            time.sleep(2)
            print("Ce démon a payé de ses crimes. Adieu, voyageur!")
            time.sleep(0.5)
            print("... Comment? Une récompense?")
            time.sleep(0.25)
            print("Prenez ce livre et arrêtez de m'importuner! Adieu!")
            rand = randint(0,5)
            print("Vous obtenez un livre de magie!")
            print("Il permet d'apprendre ",sort[rand],".")
            if mana[rand] != -1:
                print("Vous connaissez déjà ce sort. Le livre est ajouté à votre butin")
                butin += 500
            else:
                mana[rand] = 4
            time.sleep(1)
            print("")
            print("Quête accomplie!")
            print("Vous avez gagné ",50," points d'exp")
            xp(50)
            tamp = 85+randint(5,25)
            print("Vous avez gagné ",tamp," pièces d'or")
            gold = gold + tamp
            quete_3 = False
            return

        
    elif quete_4 == True:
        print("Marchand: C'est lui! Je le reconnais, c'est ce voleur!")
        time.sleep(0.25)
        print("Voleur: De quoi? Je ne me souviens pas de tous les marchands que j'ai arnaqué!")
        time.sleep(0.25)
        print("Comment? Tu crois vraiment que tu peux m'affronter?")
        time.sleep(0.5)
        combat([niv+diffi+3,"Voleur",tb_s[randint(0,2)],int(8+1.9*(niv+diffi+3)),int(11+1.8*(niv+diffi+3)),40,50])
        if fuite == True:
            time.sleep(1)
            print("")
            print("Marchand: Qu'est-ce que vous faites, aventurier?")
            time.sleep(0.25)
            print("Voleur: Tu es à merci, mon ptit marchand!")
            time.sleep(1)
            print("")
            print("Quête échouée!")
            quete_4 = False
            return
        else:
            time.sleep(1)
            print("")
            print("Mille fois merci, voyageur!")
            time.sleep(0.25)
            print("Je vais enfin pouvoir commercer de nouveau dans ce donjon!")
            time.sleep(0.25)
            print("Voilà votre récompense.")
            rand = randint(0,nb_obj)
            print("Vous obtenez un ",inv_contenu[rand*9+1],"!")
            ajout_obj(rand)
            time.sleep(0.25)
            print("Adieu voyageur!")
            time.sleep(1)
            print("")
            print("Quête accomplie!")
            print("Vous avez gagné ",50," points d'exp")
            xp(50)
            tamp = 85+randint(5,25)
            print("Vous avez gagné ",tamp," pièces d'or")
            gold = gold + tamp
            quete_4 = False
            return
        return

    
    elif quete_5 == True:
        print("Vous observez un coffre au fond de la salle")
        time.sleep(0.25)
        print("Chasseur de trésor: Ah, le voilà! Je suis sûr qu'il s'agit de ce coffre!")
        time.sleep(0.25)
        print("Il correspond à la description que l'on m'avait faite!")
        time.sleep(0.25)
        print("Je vais l'ouvrir!")
        time.sleep(0.5)
        print("Ouah, quel beau butin!")
        time.sleep(0.5)
        print("Quoi? Ah oui! Votre part!")
        time.sleep(0.25)
        print("Quelle partie du coffre voulez vous? Gauche ou droite? On peut plus choisir après, hein!")
        while act != "g" and act != "d" and act != "e":
            act = input("(g)auche - (d)roite - (e)uh... : ")
            if act == "g" or act == "d":
                time.sleep(0.25)
                print("Très bien! Voici votre part!")
                butin_quete(1)
                print("Merci beaucoup pour votre aide! A bientôt, compagnon!")
                time.sleep(1)
                print("")
                print("Quête accomplie!")
                print("Vous avez gagné ",50," points d'exp")
                xp(50)
                tamp = 45+randint(5,25)
                print("Vous avez gagné ",tamp," pièces d'or")
                gold = gold + tamp
                quete_5 = False
            elif act == "e":
                time.sleep(0.25)
                print("Vous expliquez au chasseur de trésor que vous pensez qu'il essaye de vous arnaquer.")
                time.sleep(0.5)
                print("Chasseur de trésor: Bon... C'est vrai qu'il y a un peu plus de butin sur cette partie. Tenez, prenez cette partie!")
                act2 = ""
                while act2 != "a" and act2 != "r":
                    act2 = input("(a)ccepter - (r)efuser : ")
                    if act2 == "a":
                        time.sleep(0.25)
                        print("Voilà pour vous!")
                        butin_quete(2)
                        print("Merci beaucoup pour votre aide! A bientôt, compagnon!")
                        time.sleep(1)
                        print("")
                        print("Quête accomplie!")
                        print("Vous avez gagné ",50," points d'exp")
                        xp(50)
                        tamp = 45+randint(5,25)
                        print("Vous avez gagné ",tamp," pièces d'or")
                        gold = gold + tamp
                        quete_5 = False
                        return
                    elif act2 == "r":
                        time.sleep(0.25)
                        print("Ne vous énervez pas! On peut arriver à satisfaire tout le monde!")
                        time.sleep(0.25)
                        print("Qu'est-ce que vous faites? Arrêtez!")
                        combat([1,"Chasseur de trésor",tb_s[randint(0,2)],1,10,0,50])
                        if fuite == True:
                            time.sleep(1)
                            print("")
                            print("Mais qu'est-ce qu'il fout?")
                            time.sleep(0.25)
                            print("C'est ça! Tu as bien raison d'avoir peur de... euh, moi!")
                            time.sleep(1)
                            print("")
                            print("Quête échouée!")
                            quete_5 = False
                            return
                        else:
                            print("Non... J'aurais pu me faire une fortune...")
                            butin_quete(3)
                            print("")
                            print("Quête accomplie!")
                            print("Vous avez gagné ",50," points d'exp")
                            xp(50)
                            tamp = 45+randint(5,25)
                            print("Vous avez gagné ",tamp," pièces d'or")
                            gold = gold + tamp
                            quete_5 = False
                            return
                return
        
    
#événement marchand
def marchand():
    global inv_contenu,stock,butin,gold,nb_obj,rune_lvl,rune_text,rune_act
    aurevoir = False
    print("Bien le bonjour voyageur!")
    if butin > 0:
        print("Je peux acheter votre butin pour ",butin," pièces d'or!")
    elif butin > 200:
        print("En voilà un beau butin! Je vous le prends pour ",butin," pièces d'or!")
    elif butin > 1000:
        print("Waow, sacré butin! Je vous en donne ",butin," pièces d'or!")
    gold += butin
    butin = 0
    obj_vente = []
    rand1 = randint(1,3)
    if rand1 == 3:
        rand2 = randint(0,5)
        rand3 = randint(1,100)
        if 1 <= rand3 <= 65:
            rand3 = 1
        elif 66 <= rand3 <= 85:
            rand3 = 2
        elif 86 <= rand3 <= 95:
            rand3 = 3
        elif 96 <= rand3 <= 100:
            rand3 = 4
        print("Vous avez de la chance, je possède une marchandise rare!")
        rand01 = randint(1,3)
        if rand01 == 3:
            rand02 = randint(0,5)
            rand03 = randint(1,4)
            if 1 <= rand03 <= 65:
                rand03 = 1
            elif 66 <= rand03 <= 85:
                rand03 = 2
            elif 86 <= rand03 <= 95:
                rand03 = 3
            elif 96 <= rand03 <= 100:
                rand03 = 4
            rand001 = randint(1,3)
            if rand001 == 3:
                rand002 = randint(0,5)
                rand003 = randint(1,100)
                if 1 <= rand003 <= 65:
                    rand003 = 1
                elif 66 <= rand003 <= 85:
                    rand003 = 2
                elif 86 <= rand003 <= 95:
                    rand003 = 3
                elif 96 <= rand003 <= 100:
                    rand003 = 4
    z = 0
    while z < 6:
        obj_vente.append(randint(0,nb_obj))
        z += 1
    while aurevoir == False:
        time.sleep(0.5)
        print("Voulez vous acheter quelque chose?")
        act = input("(a)cheter - (q)uitter : ")
        if act == "a":
            print("Voici ce que j'ai en stock!")
            print("")
            z = 0
            while z < 6:
                print("")
                print(z+1," -- ",inv_contenu[int(obj_vente[z])*9+1]," --         ",inv_contenu[int(obj_vente[z])*9+4]," pièces d'or")
                print("+ ",inv_contenu[int(obj_vente[z])*9+6]," pv    + ",inv_contenu[int(obj_vente[z])*9+7]," att     + ",inv_contenu[int(obj_vente[z])*9+8]," mag")
                z += 1
            if rand1 == 3:
                print("")
                print(7," -- rune ",rune_text[rand2]," niveau ",rand3," --         ",350*rand3," pièces d'or")
                print(rune_desc[rand2])
                if rand01 == 3:
                    print("")
                    print(8," -- rune ",rune_text[rand02]," niveau ",rand03," --         ",350*rand03," pièces d'or")
                    print(rune_desc[rand02])
                    if rand001 == 3:
                        print("")
                        print(9," -- rune ",rune_text[rand002]," niveau ",rand003," --         ",350*rand003," pièces d'or")
                        print(rune_desc[rand002])
            print("")
            act2 = input("Que voulez vous acheter? (1,2,3,...,(r)ien)) ")
            if act2 == "1" or act2 == "2" or act2 == "3" or act2 == "4" or act2 == "5" or act2 == "6":
                act2 = int(act2)
                print("Vous voulez acheter ",inv_contenu[int(obj_vente[act2-1])*9+1],"?")
                act3 = input("(o)ui - (n)on : ")
                if act3 == "o":
                    if gold >= int(inv_contenu[int(obj_vente[act2-1])*9+4]):
                        gold = gold - int(inv_contenu[int(obj_vente[act2-1])*9+4])
                        ajout_obj(int(obj_vente[act2-1]))
                    else:
                        print("Vous n'avez pas assez d'argent!")
                else:
                    print("Très bien!")
            elif act2 == "7":
                act2 = int(act2)
                if rand1 == 3:
                    print("Vous voulez acheter une rune ",rune_text[rand2],"?")
                    act3 = input("(o)ui - (n)on : ")
                    if act3 == "o":
                        if rune_lvl[rand2] == 0:
                            if gold >= 350*rand3:
                                rune_lvl[rand2] = rand3
                                gold = gold - 350*rand3
                            else:
                                print("Vous n'avez pas assez d'argent!")    
                        else:
                            print("Vous possédez déjà cette rune!")
                    else:
                        print("Très bien!")
                else:
                    print("Très bien!")
            elif act2 == "8":
                act2 = int(act2)
                if rand01 == 3:
                    print("Vous voulez acheter une rune ",rune_text[rand02],"?")
                    act3 = input("(o)ui - (n)on : ")
                    if act3 == "o":
                        if rune_lvl[rand02] == 0:
                            if gold >= 350*rand03:
                                rune_lvl[rand02] = rand03
                                gold = gold - 350*rand03
                            else:
                                print("Vous n'avez pas assez d'argent!")    
                        else:
                            print("Vous possédez déjà cette rune!")
                    else:
                        print("Très bien!") 
                else:
                    print("Très bien!")
            elif act2 == "9":
                act2 = int(act2)
                if rand001 == 3:
                    print("Vous voulez acheter une rune ",rune_text[rand002],"?")
                    act3 = input("(o)ui - (n)on : ")
                    if act3 == "o":
                        if rune_lvl[rand002] == 0:
                            if gold >= 350*rand003:
                                rune_lvl[rand002] = rand003
                                gold = gold - 350*rand003
                            else:
                                print("Vous n'avez pas assez d'argent!")    
                        else:
                            print("Vous possédez déjà cette rune!")
                    else:
                        print("Très bien!")
                else:
                    print("Très bien!")
            else:
                print("Très bien!")
        elif act == "q":
            print("Au revoir!")
            aurevoir = True

    
            
#------------------------------------------------------------------------------#            
#------------------------------------------------------------------------------#
#----------------------------Interface-----------------------------------------#            
#------------------------------------------------------------------------------#
#------------------------------------------------------------------------------#

            

#génère un événement aléatoire
def event():
    even = randint(1,100)
    if 1 <= even <= 5:
        print("Il n'y a rien dans la pièce...")
        time.sleep(0.3)
        print("Vous en profitez pour vous reposer!")
        time.sleep(0.5)
        soin()
    elif 6 <= even <= 20:
        quete()
    elif 21 <= even <= 77:
        print("Il y a un monstre!")
        time.sleep(0.5)
        combat(monstre())
    elif 78 <= even <= 84:
        print("Il y a un coffre!")
        time.sleep(0.5)
        coffre()
    elif 85 <= even <= 100:
        marchand()
        time.sleep(0.5)
        

#phase de repos
#plus le joueur se repose longtemps, plus il y a de chance qu'un monstre de niveau élevé arrive
def repos():
    print("")
    print("Vous vous reposez...")
    time.sleep(1.5)
    global rep, niv
    rep = rep + 1
    soin()
    aggro = randint(1,6)* rep
    if aggro >= 15:
        print("Oh oh...")
        time.sleep(0.5)
        niv = niv + rep
        combat(monstre())
        niv = niv - rep
        rep = 0


#génère un point de sauvegarde
def point_de_sauvegarde():
    global pv,pvmax,sort,mana
    time.sleep(1.5)
    print("")
    print("Vous avez atteint un point de sauvegarde!")
    time.sleep(1)
    pv = pvmax
    z = 0
    while z < len(mana):
        if mana[z] != -1:
            mana[z] = 4
        z += 1
    print("Vous sentez votre énergie vous revenir petit à petit!")
    tamp = input("Voulez-vous sauvegarder? (o)ui - (n)on : ")
    if tamp == "o":
        sauvegarder()
    

#génère le classement des différents joueurs
def classement():
    global class_contenu,tb_c,class_contenu_n,class_contenu_niv,class_contenu_c,class_contenu_t
    z = 0
    while z < len(class_contenu_t):
        class_contenu_t[z] = int(class_contenu_t[z])
        z+=1
    ranking = sorted(class_contenu_t)
    dict_n = {}
    dict_niv = {}
    dict_c = {}
    tamp = len(ranking)
    z = 0
    while z < tamp:
        dict_n[class_contenu_t[z]] = class_contenu_n[z]
        dict_niv[class_contenu_t[z]] = class_contenu_niv[z]
        dict_c[class_contenu_t[z]] = class_contenu_c[z]
        z += 1
    print(class_contenu_t)
    print("salle:")
    z = 0
    tamp2 = ""
    while z < tamp:
        print(" -- " + str(ranking[z])," -- " + str(dict_n[ranking[z]]) + ", " + str(tb_c[int(dict_c[ranking[z]])]) + " de niveau " + str(dict_niv[ranking[z]]))
        z += 1
        
        
        


#------------------------------------------------------------------------------#
#------------------------------------------------------------------------------#
        

#menu permettant d'accéder à l'inventaire, aux runes, aux stats et aux infos
def menu():
    quitter = False
    while quitter == False:
        print("")
        act001 = input("(s)tats - (i)nventaire - (r)unes - s(o)rts - i(n)fos - (q) : ")
        if act001 == "s":
            time.sleep(0.25)
            stats()
        elif act001 == "i":
            time.sleep(0.25)
            inventaire()
        elif act001 == "r":
            time.sleep(0.25)
            runes()
        elif act001 == "o":
            time.sleep(0.25)
            sorts_show()
        elif act001 == "n":
            time.sleep(0.25)
            infos()
        elif act001 == "q":
            time.sleep(0.25)
            quitter = True


#donne les statistiques du personnage
def stats():
    global n,c,niv,exp,s,pv,pvmax,att,mag,gold,diffi,tb_s,tb_c
    time.sleep(0.5)
    print("")
    print("nom : ",n,"             classe : ",tb_c[c])
    print("")
    print("niveau : ",niv,"           exp: ",exp,"/100")
    print("")
    print("or : ",gold)
    print("")
    print("élément : ",tb_s[s])
    print("pv : ",pv,"/",pvmax)
    print("attaque : ",att,"          magie : ",mag)
    print("")

    
#permet de consulter son inventaire
def inventaire():
    global inv_contenu,equipement,stock,c,niv,gold,bonusatt,bonusmag,bonuspv,pv,pvmax,att,mag,butin
    temp = 0
    str_temp = ""
    print("")
    print("tête: ",equipement[6])
    print("corps: ",equipement[7])
    print("main droite: ",equipement[4],"          main gauche: ",equipement[5])
    print("")
    print("inventaire :")
    print("1: ",stock[5])
    print("2: ",stock[6])
    print("3: ",stock[7])
    print("4: ",stock[8])
    print("5: ",stock[9])
    print("")
    act = input("(e)quiper - ajouter au (b)utin - (q) : ")
    if act == "e":
        act2 = input("Quel équipement?(1,2,3,4,5) ")
        if act2 == "1" or act2 == "2" or act2 == "3" or act2 == "4" or act2 == "5":
            act2 = int(act2)
            if int(stock[act2-1]) != -1:
                if int(inv_contenu[stock[act2-1]*9+5]) == c and int(inv_contenu[stock[act2-1]*9+3]) <= niv:
                    type_obj = int(inv_contenu[int(stock[act2-1])*9+2])
                    if pv >= int(inv_contenu[int(equipement[type_obj])*9+6]) - int(inv_contenu[int(stock[act2-1])*9+6]):
                        temp = int(equipement[type_obj])
                        str_temp = str(equipement[type_obj+4])
                        equipement[type_obj] = int(stock[act2-1])
                        equipement[type_obj+4] = str(stock[act2+4])
                        stock[act2-1] = temp
                        stock[act2+4] = str_temp
                    else:
                        print("Vous n'avez pas assez de points de vie pour changer d'équipement.")
                else:
                    print("Vous ne pouvez pas vous en équiper!")
            else:
                print("Il n'y a pas d'objet ciblé!")
        else:
            print("Veuillez cibler un objet.")
    elif act == "b":
        act2 = int(input("Quel équipement?(1,2,3,4,5) "))
        if act2 ==1 or act2 == 2 or act2 == 3 or act2 == 4 or act2 == 5:
            if int(stock[act2-1]) != -1:
                butin = butin + int(inv_contenu[int(stock[act2-1])*9+4])
                stock[act2-1] = -1
                stock[act2+4] = "/"
                print("L'objet a été ajouté au butin!")
            else:
                print("Il n'y a pas d'objet ciblé!")
        else:
            print("Veuillez cibler un objet.")
    z = 0
    pvmax = pvmax - bonuspv
    pv = pv - bonuspv
    att = att - bonusatt
    mag = mag - bonusmag
    bonuspv = bonusatt = bonusmag = 0
    while z < 4:
        if equipement[z] != -1:
            bonuspv += int(inv_contenu[int(equipement[z])*9+6])
            bonusatt += int(inv_contenu[int(equipement[z])*9+7])
            bonusmag += int(inv_contenu[int(equipement[z])*9+8])
        z+=1
    pvmax = pvmax + bonuspv
    pv = pv + bonuspv
    att = att + bonusatt
    mag = mag + bonusmag

#permet de gérer les runes possédées
def runes():
    global rune,rune_text,rune_lvl,rune_act,rune_desc
    rune_pos = False
    z = 0
    while z < len(rune):
        if rune_lvl[z] != 0:
            rune_pos = True
            print("")
            print(z+1," - rune ",rune_text[z]," niveau ",rune_lvl[z])
            if rune_act == z:
                print("rune équipée")
            print("")
            print(rune_desc[z])
            print("")
        z+=1
    print("")
    if rune_pos == False:
        print("Vous ne possédez pas de runes!")
    else:
        act1 = input("(e)quiper/déséquiper - (q)uitter : ")
        if act1 == "e":
            act2 = input("Lequel? (1,2,3...) ")
            if act2 == "1" or act2 == "2" or act2 == "3" or act2 == "4" or act2 == "5" or act2 == "6":
                act2 = int(act2)
                if rune_lvl[act2-1] != 0:
                    time.sleep(0.3)
                    if rune_act == act2-1:
                        rune_act = -1
                        print("Rune déséquipée!")
                    else:
                        rune_act = act2-1
                        print("Rune équipée!")
                else:
                    print("Veuillez sélectionner une rune possédée.")
            else:
                print("Veuillez sélectionner une rune possédée.")         
                
#permet de consulter ses sorts disponibles
def sorts_show():
    global mana,sort,sort_desc,s,tb_s
    print("")
    print("boule de ",tb_s[s],"     mana: /")
    print("Sort de base élémentaire")
    print("")
    z = 0
    while z < len(sort):
        if mana[z] != -1:
            print(sort[z],"     mana: ",mana[z])
            print(sort_desc[z])
            print("")
        z += 1

#donne des indications sur le fonctionnement du jeu
def infos():
    print("")
    print("Quels renseignements voulez-vous?")
    temp2 = input("(e)lements - (a)vancer - (r)epos - (m)agie - (b)utin : ")
    print("")
    if temp2 == "e":
        print("Il existe trois éléments: le feu, la glace et la foudre. Vous avez une affinité avec un de ces éléments, vous permettant de lancer des sorts de cet élément.")
        print("Il y a un triangle d'efficacité avec ces éléments: le feu est supérieur à la glace, la foudre est supérieure au feu, et la glace est supérieure à la foudre.")
    elif temp2 == "a":
        print("La commande avancer permet de progresser dans le donjon, de le parcourir pièce par pièce. La pièce peut soit contenir un monstre, soit contenir un coffre, soit être vide.")
    elif temp2 == "r":
        print("Vous reposer vous permet de vous soigner. Par contre, attention à ne pas rester trop longtemps dans la même pièce, certains gros monstres errants pourraient venir...")
    elif temp2 == "m":
        print("Lorsque vous affrontez un monstre avec votre magie, vous vous exposez à lui. Si vous ne réussissez pas à le tuer d'un seul coup, les représailles pourraient être fatales!")
    elif temp2 == "b":
        print("Les pièces d'or peuvent être récupérées sur des monstres ou bien dans des coffres. Les pièces d'or vous permettent de vous enfuir, pour 50 pièces d'or.")



#------------------------------------------------------------------------------#
#------------------------------------------------------------------------------#
#-------------------------------Sauvegarde-------------------------------------#
#------------------------------------------------------------------------------#
#------------------------------------------------------------------------------#

#intro
def nouvpartie():
    global n,c,niv,exp,s,pv,pvmax,att,mag,gold,diffi
    print("Bienvenue dans l'univers de Saitrobïn !")
    time.sleep(0.5)
    print("Vous voici devant le donjon de Rande Haume!")
    time.sleep(0.5)
    print("En tant que héros chevronné, vous vous devez d'entrer à l'intérieur!")
    time.sleep(0.5)
    print("Mais tout d'abord, présentez-vous.")
    time.sleep(1)
    print("")
    n=input("Entrez votre nom : ")
    c=int(input("Entrez votre classe (0:guerrier, 1:archer, 2:mage) : "))
    s=int(input("Entrez votre élément de prédilection(0:feu, 1:foudre, 2:glace): "))
    diffi=int(input("Choisissez la difficulté: 0:très facile 1:facile 2:normal  3:difficile  4:expert  5:légendaire : "))
    print("Parfait ! Entrez maintenant dans le donjon...")
    time.sleep(0.5)

    #Définition des stats en fonction de la classe
    #Le joueur est pénalisé si il n'a pas respecté les choix proposés pour la classe
    if c == 0:
        pvmax = pvmax + 20
        pv = pv + 20
        mag = mag - 5
    elif c == 1:
        pvmax = pvmax - 20
        pv = pv - 20
        att = att + 5
    elif c == 2:
        att = 10 - 3
        mag = 10 + 5
    else:
        pvmax = pvmax - 20
        pv = pv - 10
        att = att - 2
        mag = mag - 2
        c = 3
    #Définit aléatoirement un élément pour le joueur si il n'en a pas défini un
    if s != 0 and s != 1 and s != 2:
        s = randint(0,2)
    #Définit une difficulté par défaut si aucune difficulté n'et choisi
    if diffi != 0 and diffi != 1 and diffi != 2 and diffi != 3 and diffi != 4 and diffi != 5:
        diffi = 2


#Permet de charger une partie existante
def charger():
    global n,c,niv,exp,s,pv,pvmax,att,mag,gold,temps,rep,diffi,stock,equipement,rune_act,rune_lvl,rune_xp,mana,quete_1,quete_2,quete_3,quete_4,quete_5,ch_type,ch_nb,ch_nbmax,bonuspv,bonusatt,bonusmag
    q = False
    while q == False:
        char = input("Quelle partie à charger? ")
        name = str(char)+".txt"
        try:
            save = open(name,"r")
        except IOError:
            print("Erreur lors de l'ouverture du fichier.")
        else:
            ry = 0
            q = True
            contenu = save.readlines()
            while ry < len(contenu):
                terme = contenu[ry]
                fin = len(terme)-1
                tampon = terme[0:fin]
                contenu[ry] = tampon
                ry+=1
            n = str(contenu[0])
            c = int(contenu[1])
            s = int(contenu[2])
            niv = int(contenu[3])
            exp = int(contenu[4])
            gold = int(contenu[5])
            pv = int(contenu[6])
            pvmax = int(contenu[7])
            att = int(contenu[8])
            mag = int(contenu[9])
            temps = int(contenu[10])
            rep = int(contenu[11])
            diffi = int(contenu[12])
            butin = int(contenu[13])
            equipement[0] = int(contenu[14])
            equipement[1] = int(contenu[15])
            equipement[2] = int(contenu[16])
            equipement[3] = int(contenu[17])
            equipement[4] = str(contenu[18])
            equipement[5] = str(contenu[19])
            equipement[6] = str(contenu[20])
            equipement[7] = str(contenu[21])
            stock[0] = int(contenu[22])
            stock[1] = int(contenu[23])
            stock[2] = int(contenu[24])
            stock[3] = int(contenu[25])
            stock[4] = int(contenu[26])
            stock[5] = str(contenu[27])
            stock[6] = str(contenu[28])
            stock[7] = str(contenu[29])
            stock[8] = str(contenu[30])
            stock[9] = str(contenu[31])
            rune_lvl[0] = int(contenu[32])
            rune_lvl[1] = int(contenu[33])
            rune_lvl[2] = int(contenu[34])
            rune_lvl[3] = int(contenu[35])
            rune_lvl[4] = int(contenu[36])
            rune_lvl[5] = int(contenu[37])
            rune_xp[0] = int(contenu[38])
            rune_xp[1] = int(contenu[39])
            rune_xp[2] = int(contenu[40])
            rune_xp[3] = [int(contenu[41]),int(contenu[42])]
            rune_xp[4] = [int(contenu[43]),int(contenu[44])]
            rune_xp[5] = [int(contenu[45]),int(contenu[46])]
            rune_act = int(contenu[47])
            mana[0] = int(contenu[48])
            mana[1] = int(contenu[49])
            mana[2] = int(contenu[50])
            mana[3] = int(contenu[51])
            mana[4] = int(contenu[52])
            quete_1 = bool(contenu[53])
            quete_2 = bool(contenu[54])
            quete_3 = bool(contenu[55])
            quete_4 = bool(contenu[56])
            quete_5 = bool(contenu[57])
            ch_type = str(contenu[58])
            ch_nb = int(contenu[59])
            ch_nbmax = int(contenu[60])
            bonuspv = int(contenu[61])
            bonusatt = int(contenu[62])
            bonusmag = int(contenu[63])
            
            
            save.close()
            print("Partie chargée!")
            print("Vous revoilà, ",n,"!")
            

#Sauvegarder la partie acuelle
def sauvegarder():
    global n,c,niv,exp,s,pv,pvmax,att,mag,gold,temps,rep,diffi,stock,equipement,rune_act,rune_lvl,rune_xp,class_contenu,classement,quete_1,quete_2,quete_3,quete_4,quete_5,ch_type,ch_nb,ch_nbmax,bonuspv,bonusatt,bonusmag
    name = str(n)+".txt"
    save = open(name,"w")
    rune_xp3 = rune_xp[3]
    rune_xp4 = rune_xp[4]
    rune_xp5 = rune_xp[5]
    save.write(str(n)+"\n"+str(c)+"\n"+str(s)+"\n"+str(niv)+"\n"+str(exp)+"\n"+str(gold)+"\n"+str(pv)+"\n"+str(pvmax)+"\n"+str(att)+"\n"+str(mag)+"\n"+str(temps)+"\n"+str(rep)+"\n"+str(diffi)+"\n"+str(butin)+"\n"+str(equipement[0])+"\n"+str(equipement[1])+"\n"+str(equipement[2])+"\n"+str(equipement[3])+"\n"+str(equipement[4])+"\n"+str(equipement[5])+"\n"+str(equipement[6])+"\n"+str(equipement[7])+"\n"+str(stock[0])+"\n"+str(stock[1])+"\n"+str(stock[2])+"\n"+str(stock[3])+"\n"+str(stock[4])+"\n"+str(stock[5])+"\n"+str(stock[6])+"\n"+str(stock[7])+"\n"+str(stock[8])+"\n"+str(stock[9])+"\n"+str(rune_lvl[0])+"\n"+str(rune_lvl[1])+"\n"+str(rune_lvl[2])+"\n"+str(rune_lvl[3])+"\n"+str(rune_lvl[4])+"\n"+str(rune_lvl[5])+"\n"+str(rune_xp[0])+"\n"+str(rune_xp[1])+"\n"+str(rune_xp[2])+"\n"+str(rune_xp3[0])+"\n"+str(rune_xp3[1])+"\n"+str(rune_xp4[0])+"\n"+str(rune_xp4[1])+"\n"+str(rune_xp5[0])+"\n"+str(rune_xp5[1])+"\n"+str(rune_act)+"\n"+str(mana[0])+"\n"+str(mana[1])+"\n"+str(mana[2])+"\n"+str(mana[3])+"\n"+str(mana[4])+"\n"+str(int(quete_1))+"\n"+str(int(quete_2))+"\n"+str(int(quete_3))+"\n"+str(int(quete_4))+"\n"+str(int(quete_5))+"\n"+str(ch_type)+"\n"+str(ch_nb)+"\n"+str(ch_nbmax)+"\n"+str(bonuspv)+"\n"+str(bonusatt)+"\n"+str(bonusmag)+"\n")
    save.close

    sauvegarde_class()
            
    print("Partie sauvegardée!")

    
#sauvegarde dans le classement
def sauvegarde_class():
    class_contenu,class_contenu_n,class_contenu_niv,class_contenu_c,class_contenu_t
    inter00 = False
    z = 0
    tamp = ""
    while z < len(class_contenu_n):
        if class_contenu_n[z] == n:
            class_contenu_niv[z] = niv
            class_contenu_c[z] = c
            class_contenu_t[z] = temps+1
            tamp = tamp + str(class_contenu_n[z])+"\n"+str(class_contenu_niv[z])+"\n"+str(class_contenu_c[z])+"\n"+str(class_contenu_t[z])+"\n"
            inter00 = True
            z += 1
        else:
            tamp = tamp + str(class_contenu_n[z])+"\n"+str(class_contenu_niv[z])+"\n"+str(class_contenu_c[z])+"\n"+str(class_contenu_t[z])+"\n"
            z += 1
        
    if inter00 == False:
        class_contenu_n.append(n)
        class_contenu_niv.append(niv)
        class_contenu_c.append(c)
        class_contenu_t.append(temps+1)
        tamp = tamp + str(n)+"\n"+str(niv)+"\n"+str(c)+"\n"+str(temps+1)+"\n"
    classement = open("classement.txt","w")
    classement.write(tamp)
    classement.close
    

#------------------------------------------------------------------------------#
#------------------------------------------------------------------------------#
#---------------------------DEROULEMENT----------------------------------------#
#------------------------------------------------------------------------------#
#------------------------------------------------------------------------------#

while partie == False:
    ent=input("(n)ouvelle partie - (c)harger : ")
    if ent == "n" :
        nouvpartie()
        partie = True
    elif ent == "c" :
        charger()
        partie = True


#Boucle permettant de parcourir les différentes pièces
while temps < 1000:
    fuite = False
    if loose == True:
        print("Vous êtes mort!")
        time.sleep(4)
        temps = 1000
    else:
        time.sleep(0.7)
        if temps%25 == 9:
            point_de_sauvegarde()
            temps = temps + 1
        else:
            print("")
            print("points de vie :",pv,"  pièce : ",temps+1,"  étage : ",temps//50+1)
            print("")
            temp = input("(a)vancer - (r)eposer - (m)enu - (c)lassement: ")
            if temp == "a" :
                event()
                temps = temps + 1
            elif temp == "r" :
                repos()
            elif temp == "m" :
                menu()
            elif temp == "c" :
                classement()