fprintf(' -> \t Super AES \n');
fprintf(' ->1<- \t 320 bits \n ->2<- \t 480 bits \n ->3<- \t 640 bits \n ');
choix_key = input('Choix de la taille d''une cle :\n ');

if choix_key==1
    Nb=4; %nombre de colonne de la clé sous forme matricielle
    Nr=10; %Nombre de tours
elseif choix_key==2
    Nb=6;
    Nr=12;
elseif choix_key==3
    Nb=8;
    Nr=14;
end

%% Chiffrement

path='texte_a_chiffrer.txt';
B=16; %nombre de bits par bloc
[ texte_clair_hexa ] = texte_hexa_lecture(path,B);

[ S,V,W1,W ] = Generateur(); %poly irréductible, générateur et élément

random_key(Nb); %création d'une clé aléatoire

aes_encrypt(texte_clair_hexa,W,Nb,Nr)


%% Déchiffrement

path='texte_chiffré.txt';
B=16; %nombre de bits par bloc
[ texte_chiffre_hexa ] = texte_hexa_lecture(path,B);

aes_decrypt(texte_chiffre_hexa,W,Nb,Nr);


