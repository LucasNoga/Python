Énoncé



Les trending topics sont des hashtags fréquents sur Twitter. Dans ce challenge on va considérer qu'il se crée un trending topic si un hashtag apparaît au minimum 40 fois dans une fenêtre de 60 minutes.



Le but de ce challenge est de déterminer s'il existe un trending topic dans un flux de hashtags. On considére qu'il s'écoule une minute entre deux hashtags du flux et donc qu'une fenêtre de 60 minutes contient 60 tags.



Format des données



Entrée

Ligne 1 : un entier N compris entre 1 et 1000 correspondant au nombre de hashtags du flux.

Lignes 2 à N+1 : un hashtag Twitter. Un hashtag est composé de lettres minuscules non accentuées précédées par le symbole #.



Sortie

Une chaine de caractères (commençant par le symbole #) correspondant au premier (chronologiquement) trending topic s'il y en a un, sinon la chaîne Pas de trending topic



#*****
#Solution by ISOGRAD
#*****

from collections import Counter

def trending_topic(bundle):
    hashtags = []
    for hashtag in bundle:
        hashtags.append(hashtag)
        if len(hashtags) == SIZE:
            c = Counter(hashtags)
        if len(hashtags) > SIZE:
            c[hashtag] += 1
            c[hashtags[-(SIZE + 1)]] -= 1
        if len(hashtags) >= SIZE:
            for hashtag in c:
                if c[hashtag] >= 2 * SIZE / 3:
                    return hashtag
    return "Pas de trending topic"

SIZE = 60

N = int(input())
hashtags = []
c = {}
for _ in range(N):
    hashtags.append(input())
print(trending_topic(hashtags))

