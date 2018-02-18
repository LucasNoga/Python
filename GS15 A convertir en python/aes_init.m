function [state ] = aes_init(taille,n,texte_clair_hexa)
%permet de former la matrice => state

k=1+(n-1)*20;

 for i = 1:5
     for j=1:4
         if k <= taille
             state(i,j)=texte_clair_hexa(k);
             k=k+1;
         else
            state(i,j)=0;
         end
     end
 end
 
end

 