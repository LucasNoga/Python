function afficher_texte_dechiffre( state,n)
%retrancrire �l�ment d�cimal en texte

chaine='';

for i=1:5
    for j=1:4
        a=dec2bin(state(i,j),16);
        gauche=a(1:length(a)-8);
        droite=a(length(a)-7:length(a));
        lettre1=native2unicode(bin2dec(gauche));
        lettre2=native2unicode(bin2dec(droite));
        chaine=[chaine,lettre1,lettre2];
    end
end

if n==1
    fid=fopen('texte_d�chiffr�.txt','w');
    fprintf(fid,'%c',chaine);
    fclose(fid);
else
    fid=fopen('texte_d�chiffr�.txt','a+');
    fprintf(fid,'%c',chaine);
    fclose(fid);
end

end

