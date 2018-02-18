function aes_encrypt( texte_clair_hexa,W,Nb,Nr )

fprintf('***************************** \n')
fprintf('*******  Chiffrement  ******* \n')
fprintf('***************************** \n')

taille=size(texte_clair_hexa,1);

tour_texte=ceil(taille/20); %permet de chiffre le texte en son entier

for k=1:tour_texte
    
fprintf('State initial');
[state] = aes_init(taille,k,texte_clair_hexa) %state initial

fprintf('State apres AddRoundKey');
state = AddRoundKey(state, 0, Nb)

 for i=1:Nr-1
      fprintf('State au round n°%d apres SubBytes :', i)
      state=SubBytes(state,W)
      fprintf('State au round n°%d apres ShiftRows :', i)
      state = ShiftRows(state)
      fprintf('State au round n°%d apres mixColumns :', i)
      state = MixColumns(state)
      fprintf('State au round n°%d apres AddRoundKey :', i)
      state = AddRoundKey(state, i, Nb)
 end

 fprintf('State au dernier tour apres SubBytes :')
 state=SubBytes(state,W)
 fprintf('State au dernier tour apres ShiftRows :')
 state=ShiftRows(state)
 fprintf('State final :')
 state = AddRoundKey(state,Nr,Nb)
 
 afficher_texte_chiffre(state,k); %retrancrire en fichier texte
 
end

end

