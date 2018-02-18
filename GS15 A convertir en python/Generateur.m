function [ S,V,W1,W ] = Generateur()

read(symengine,'Untitled7.mu');
P=feval(symengine,'polirreductible',16); %polynome irréductible
Q=feval(symengine,'generateur',P); %polynome générateur
T=[1:65536];
S=[1:1];
V=[1:1];
V(1,1)=feval(symengine,'polytodec',Q); %conversion polynome -> décimal

S(1,1)=feval(symengine,'polytodec',P);

%on génère les éléments
T(1,1)=feval(symengine,'element',P,Q,0); % ^0
T(1,2)=feval(symengine,'element',P,Q,1); % ^1


for i = 3:65536
    
 T(1,i)=poly_mult(T(1,i-1),T(1,2),S(1,1));

end

W1=[1:256;1:256];

k=1;

for i=1:256
    for j=1:256
        
        W1(i,j)=T(1,k);
        k=k+1;
        
    end
    
end

W=[1:256;1:256];

k=1;

for i=1:256
    for j=1:256
        
        W(257-i,257-j)=T(1,k);
        k=k+1;
        
    end
    
end


end

