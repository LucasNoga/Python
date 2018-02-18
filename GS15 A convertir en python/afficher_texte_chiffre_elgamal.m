function afficher_texte_chiffre_elgamal( Chiffre,n)

chaine='';

MsgChiffre=[1:2];

%couple C1,C2 du message chiffré
MsgChiffre(1)=feval(symengine,'polytodec',Chiffre(1)); 
MsgChiffre(2)=feval(symengine,'polytodec',Chiffre(2));

a=dec2bin(MsgChiffre(1),16);
gauche=a(1:length(a)-8);
droite=a(length(a)-7:length(a));
lettre1=native2unicode(bin2dec(gauche));
lettre2=native2unicode(bin2dec(droite));

b=dec2bin(MsgChiffre(2),16);
gauche=b(1:length(b)-8);
droite=b(length(b)-7:length(b));
lettre3=native2unicode(bin2dec(gauche));
lettre4=native2unicode(bin2dec(droite));

chaine=[chaine,lettre1,lettre2,lettre3,lettre4];


if n==1
    fid=fopen('texte_chiffré_elgamal.txt','w');
    fprintf(fid,'%c',chaine);
    fclose(fid);
else
    fid=fopen('texte_chiffré_elgamal.txt','a+');
    fprintf(fid,'%c',chaine);
    fclose(fid);
end

end

