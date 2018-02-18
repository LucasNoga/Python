function [ key ] = KeyExpansion(Nb,round)

if round==0
[key] = calcul_key(Nb); %clé initiale
else %on "change" la clé
    for i=1:round
        [key]=ShiftRows(calcul_key(Nb));
    end
end
 
end

 

