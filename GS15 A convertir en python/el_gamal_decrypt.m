function el_gamal_decrypt( texte_chiffre_hexa,x,P )

fprintf('***************************** \n')
fprintf('******* Déchiffrement ******* \n')
fprintf('***************************** \n')

Gy=texte_chiffre_hexa(1);
Gy=dectopoly(Gy);

cp=feval(symengine,'powermod',Gy,65535-x,P); %calculer l'inverse de ((G^y)^x)^-1
cp=feval(symengine,'powermod',cp,1,2);


for i =1: length(texte_chiffre_hexa)
    if mod(i-1,2)~=0 %permet de ne traiter que le 2ème élément du couple C1 C2
        MHy=texte_chiffre_hexa(i);
        
        MHy=dectopoly(MHy);
    
        clair=MHy*cp;
        clair=feval(symengine,'powermod',clair,1,P);
        clair=feval(symengine,'powermod',clair,1,2)
        
        afficher_texte_dechiffre_elgamal(clair,i-1);
    end
end

end

