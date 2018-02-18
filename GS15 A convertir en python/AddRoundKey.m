function [ state ] = AddRoundKey(state,round,Nb)

[key]=KeyExpansion(Nb,round);
 
 key = key(:,[1:4]); %il faut que state et key soient de mm dimensions
 
state = bitxor (state, key); % XOR matrice et clé

end

 

