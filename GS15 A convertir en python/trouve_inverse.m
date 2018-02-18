function [ sortie ] = trouve_inverse( entree, mod_pol )


for i=1:65535
    if poly_mult(entree,i,mod_pol)~=1
    sortie=i;
    end
end

end


