function [ out,a,b ] = recherche_element(elt,W)
%permet de trouver l'inverse

k=1;
a=0;
b=0;
l=0;
c=0;
out=0;
for i=1:256
    for j=1:256
        
        if W(i,j) == elt
            %fprintf('%d \n',i);
            a=i;
            %fprintf('%d \n',j);
            b=j;
        end
        k=k+1;
        
    end
    
end
l=257-a;
%fprintf('%d \n',l);
c=257-b;
%fprintf('%d \n',c);
out=W(l,c);

end

