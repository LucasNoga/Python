function [ key ] = random_key(Nb)

for i=1:5
    for j=1:Nb
        X = round(rand*(2^16-1)); %clé aléatoire
        Xbin = dec2bin(X,8);
        Xhexa = bin2dec(Xbin);
        key(i,j)=Xhexa;
    end
end

key;

%retranscription decimal => texte
chaine='';

for i=1:5
    for j=1:Nb
        a=dec2bin(key(i,j),16);
        gauche=a(1:length(a)-8);
        droite=a(length(a)-7:length(a));
        lettre1=native2unicode(bin2dec(gauche));
        lettre2=native2unicode(bin2dec(droite));
        chaine=[chaine,lettre1,lettre2];
    end
end

fid=fopen('key.txt','w');
fprintf(fid,'%c',chaine);
fclose(fid);

end
