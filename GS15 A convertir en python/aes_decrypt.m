function aes_decrypt( texte_chiffre_hexa,W,Nb,Nr )

fprintf('***************************** \n')
fprintf('******* Déchiffrement ******* \n')
fprintf('***************************** \n')

taille=size(texte_chiffre_hexa,1);

tour_texte=ceil(taille/20); %permet de chiffrer le texte en son entier

for k=1:tour_texte
  
fprintf('State initial');
[state] = aes_init(taille,k,texte_chiffre_hexa) %state initial

fprintf('State apres AddRoundKey');
state = AddRoundKey(state, Nr, Nb)

fprintf('State apres InvShiftRows');
state=InvShiftRows(state)

fprintf('State apres InvSubBytes :')
state=InvSubBytes(state,W)
 
 for i=Nr-1:-1:1
    fprintf('State au round n°%d après AddRoundKey :',Nr-i)
    state = AddRoundKey(state,i, Nb)
    fprintf('State au round n°%d après InvMixColumns :',Nr-i)
    state = InvMixColumns(state)
    fprintf('State au round n°%d après InvShiftRows :',Nr-i)
    state = InvShiftRows(state)
    fprintf('State au round n°%d après InvSubBytes :',Nr-i)
    state = InvSubBytes(state,W)
 end
 
 fprintf('State final :')
 state = AddRoundKey(state,0,Nb)
 
 afficher_texte_dechiffre(state,k);
 
end

end

