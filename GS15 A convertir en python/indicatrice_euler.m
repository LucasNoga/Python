function [ phi ] = indicatrice_euler( P )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

decomp=factor(P);

taille=length(decomp);

phi=1;

i=1;

while i<=taille 
    
    exp=0;
    
    
        for k=1:taille
            if decomp(i)==decomp(k)
                exp=exp+1;
            end        
        end
    
    
    phi=phi*((decomp(i)^(exp-1))*(decomp(i)-1));
    
    i=i+exp;
end

phi;

end

