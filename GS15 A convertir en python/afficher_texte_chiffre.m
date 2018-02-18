function afficher_texte_chiffre( state,n)

chaine='';

%chaque élément est composé de 16 bits
%et donc de deux lettres

for i=1:5
    for j=1:4
        a=dec2bin(state(i,j),16);
        gauche=a(1:length(a)-8);
        droite=a(length(a)-7:length(a));
        lettre1=native2unicode(bin2dec(gauche));
        lettre2=native2unicode(bin2dec(droite)); %conversion en ASCII
        chaine=[chaine,lettre1,lettre2];
    end
end

if n==1
    fid=fopen('texte_chiffré.txt','w');
    fprintf(fid,'%c',chaine);
    fclose(fid);
else
    fid=fopen('texte_chiffré.txt','a+');
    fprintf(fid,'%c',chaine);
    fclose(fid);
end

end

