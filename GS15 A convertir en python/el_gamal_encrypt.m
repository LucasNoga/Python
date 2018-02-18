function [ P,g,x,y ] = el_gamal_encrypt(texte_clair_hexa)

fprintf('***************************** \n')
fprintf('*******  Chiffrement  ******* \n')
fprintf('***************************** \n')

read(symengine,'Untitled3.mu');
P=feval(symengine,'polirreductible',16); %polynome irreductible
g=feval(symengine,'generateur',P); %générateur

x=round(rand*(2^16-1));
y=round(rand*(2^16-1));

while gcd(y,65535)~=1
    y=round(rand*(2^16-1));
end

Gy=feval(symengine,'powermod',g,y,P);
Gy=feval(symengine,'powermod',Gy,1,2);

h=feval(symengine,'powermod',g,x,P);
h=feval(symengine,'powermod',h,1,2);


for i = 1 : length(texte_clair_hexa)
    M=texte_clair_hexa(i);
    M=dectopoly(M);

    Hy=feval(symengine,'powermod',h,y,P);
    Hy=feval(symengine,'powermod',Hy,1,2);

    MHy=M*Hy;
    MHy=feval(symengine,'powermod',MHy,1,P);
    MHy=feval(symengine,'powermod',MHy,1,2);

    Chiffre=[Gy,MHy]
    
    afficher_texte_chiffre_elgamal(Chiffre,i);
end

end

