
"""
a = 3
print(a)
a += 3
b = a - 2
print("a =", a, "et b =", b)
"""


"""
prenom = "Lucas"
nom = "Noga"
age = 20
print("Je m'appelle {0} {1} et j'ai {2} ans.".format(prenom, nom, age))
"""


"""
formatage d'une adresse
adresse = ""
{no_rue}, {nom_rue}
{code_postal} {nom_ville} ({pays})
"".format(no_rue=5, nom_rue="rue des Postes", code_postal=75003, nom_ville="Paris", 
pays="France")
print(adresse)
"""


"""
# identite = "{nom} {prenom} {age} ans".format(nom="Noga", prenom="Lucas", age=20)
# print(identite + " " + adresse)
"""


"""
# placard = {"chemise":3, "pantalon":6, "tee shirt":7}
# print(placard.pop("pantalon"))
# print(placard)
"""


"""
# print(locals())
"""


"""
count = int(input())
for i in range(count):
    line = input()
"""


"""
print(max([45, 60, 200], [32, 75, 210], [57, 75, 0]))
print(sum([45, 60, 200]), sum([32, 75, 210]), sum([32, 75, 210]))
"""

"""
print("salut je suis la sortie standard")
print("salut je suis la sortie d'erreur", file=sys.stderr)
"""

"""
for _ in range(10):
    print(1)
"""


"""
dico = {1: 'e', 2: 'o', 3: 'i', 4: 'u', 5: 'y', 6: 't', 7: 'a'}
for x in dico.values():
    print(x)
for x, y in dico.items():
    print(x, y)
dico_restreint = {x:y for x, y in dico.items() if y>'l'}
print(dico_restreint)
"""