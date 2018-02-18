function afficher_texte_dechiffre_elgamal( clair,n)

chaine='';

MsgClair=[1:1];

MsgClair(1)=feval(symengine,'polytodec',clair);


a=dec2bin(MsgClair(1),16);
gauche=a(1:length(a)-8);
droite=a(length(a)-7:length(a));
lettre1=native2unicode(bin2dec(gauche));
lettre2=native2unicode(bin2dec(droite));


chaine=[chaine,lettre1,lettre2];


if n==1
    fid=fopen('texte_déchiffré_elgamal.txt','w');
    fprintf(fid,'%c',chaine);
    fclose(fid);
else
    fid=fopen('texte_déchiffré_elgamal.txt','a+');
    fprintf(fid,'%c',chaine);
    fclose(fid);
end

end

