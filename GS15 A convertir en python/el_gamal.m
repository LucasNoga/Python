fprintf(' -> \t Super El-Gamal \n');

%% Chiffrement

path='texte_a_chiffrer.txt';
B=16; %nombre de bits par bloc
[ texte_clair_hexa ] = texte_hexa_lecture(path,B);

[P,g,x,y]=el_gamal_encrypt(texte_clair_hexa);

%% Signature

HM=texte_clair_hexa(1);

[h,r,s] = Signature(HM,x,y,P,g);

%% Déchiffrement

path='texte_chiffré_elgamal.txt';
B=16; %nombre de bits par bloc
[ texte_chiffre_hexa ] = texte_hexa_lecture(path,B);

el_gamal_decrypt(texte_chiffre_hexa,x,P);

%% Verification de la signature

path='texte_déchiffré_elgamal.txt';
B=16; %nombre de bits par bloc
[ texte_dechiffre_hexa ] = texte_hexa_lecture(path,B);

HM=texte_dechiffre_hexa(1);

Verif_Signature(HM,r,s,h,P,g);

