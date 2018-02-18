function [ key ] = calcul_key(Nb)
%permet de mettre la clé sous forme matricielle

path = 'key.txt';
B=16; %nombre de bits par bloc  

[ key_hex ] = texte_hexa_lecture(path,B);

taille=size(key_hex,1);
k=1;

 for i = 1:5
     for j=1:Nb
         if k <= taille
             key(i,j)=key_hex(k);
             k=k+1;
         else
            key(i,j)=0;
         end
     end
 end

end

