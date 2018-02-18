print("Codage d'un mot en binaire 0'")

message = input("Saisir un mot : ")
answer = ""

# fonction qui construit le binaire
def prepare_answer(bit_type, count, flag_without_trailing_space=False):
    resultat = ""
    if bit_type == 1:
        resultat += "0"
    else:
        resultat += "00"
    resultat += " "
    for i in range(0, count):
        resultat += "0"
    if not flag_without_trailing_space:
        resultat += " "
    return resultat

characters = list(message)
bits = []
for char in characters:
    # Iteration pour chaque bit
    for i in reversed(range(0, 7)):
        bit = (ord(char) >> i) & 0x01
        bits.append(bit)

bit_type = 0
count = 0

for bit in bits:
    if count == 0:
        if bit == 1:
            bit_type = 1
        else:
            bit_type = 0
        count += 1
    else:
        if bit != bit_type:
            answer += prepare_answer(bit_type, count)
            bit_type = bit
            count = 1
        else:
            count += 1

answer += prepare_answer(bit_type, count, flag_without_trailing_space=True)

print(answer)
