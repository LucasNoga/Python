function ab = poly_mult (a, b, mod_pol)

%bitget(A,bit) : This MATLAB function returns the bit value at position bit in integer array A.
%bitshift(A,k) : This MATLAB function returns A shifted to the left by k bits, equivalent to multiplying by 2k

ab = 0;

% Boucle sur chaque bit du premier facteur ("a" ) en commençant par le bit
%le moins significatif . Cette boucle multiplie "a" et "b" modulo 2
for pos = 1 : 16
    if bitget (a, pos)
        b_mult = bitshift (b, pos - 1);
        ab = bitxor (ab, b_mult);
    end
end

%Boucle sur les 16 bits les plus significatifs du produit "ab" . 
%Cette boucle permet de réduire le produit (32 bits) 
%à 16 bits => GF 2^16 
%par l'utilisation d'un polynôme irréductible
for pos = 32 : -1 : 17
    if bitget (ab, pos)
        mod_pol_mult = bitshift (mod_pol, pos - 17);
        ab = bitxor (ab, mod_pol_mult);
    end
end

end