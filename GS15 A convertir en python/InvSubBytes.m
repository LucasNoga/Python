function [ state ] = InvSubBytes( state,W )
%on xor le state avec Cprim
%puis on multiplie chaque élément par Aprim

Cprim='';

Aprim=[1 0 1 1 1 1 0 0 1 1 0 0 1 1 0 0 ;...
       1 1 1 0 0 0 1 0 1 0 1 0 1 0 1 0 ;...
       1 1 0 0 1 1 0 1 1 0 0 1 1 0 0 1 ;...
       0 1 1 1 1 0 0 1 0 1 0 1 0 1 1 1 ;...
       1 0 0 1 1 1 1 1 1 1 1 1 1 1 0 0 ;...
       1 1 1 1 0 0 1 1 0 0 1 1 0 0 1 0 ;...
       0 1 1 1 1 0 0 1 1 0 0 1 1 0 0 1 ;...
       0 0 1 0 0 0 1 1 0 1 0 1 0 1 1 1 ;...
       1 0 1 1 0 0 1 0 1 1 1 1 1 1 0 0 ;...
       1 1 1 0 0 1 0 1 1 0 1 1 0 0 1 0 ;...
       1 1 0 0 1 1 1 0 0 0 0 1 0 1 0 1 ;...
       1 1 0 0 0 1 0 0 0 1 0 1 1 1 0 1 ;...
       1 1 0 0 0 0 0 1 0 1 1 1 1 0 0 1 ;...
       1 1 0 0 0 0 1 1 1 1 1 0 1 0 1 1 ;...
       0 1 1 1 1 1 1 0 0 1 1 0 1 1 1 0 ;...
       0 0 1 1 1 1 1 1 0 0 1 1 0 1 1 1 ];
cprim = [1 0 0 1 1 1 0 0 1 0 0 1 1 1 0 0];

for k=1:16
    Cprim=[Cprim,dec2bin(cprim(1,k))];
end

Cprim=bin2dec(Cprim);

temp = zeros(5,4);

% test

for i=1:5
    for j=1:4
        
        temp3=bitxor(Cprim,state(i,j));
        
        temp3=dec2bin(temp3,16);
        chaine={temp3(1) temp3(2) temp3(3) temp3(4) temp3(5) temp3(6) temp3(7) temp3(8) temp3(9) temp3(10) temp3(11) temp3(12) temp3(13) temp3(14) temp3(15) temp3(16)}; 
        
        temp3=[1:16];
        for k = 1:16
            temp3(1,k)=bin2dec(chaine(1,k));
        end
        
        mult=zeros(1,16);

        for l=1:16
            for m=1:16
                mult(1,l)=mult(1,l)+Aprim(l,m)*temp3(1,m);
            end
        end
        
        for k=1:16
            mult(1,k)=mod(mult(1,k),2);
        end      
      
        temp2='';
        
        for k = 1:16
            temp2=[temp2,dec2bin(mult(1,k))];
        end
        
        temp2=bin2dec(temp2);
        
        if temp2 ~= 0
            inverse=recherche_element(temp2,W); %on recherche l'inverse
        else
            inverse=0;
        end;
        
        temp(i,j)=inverse;

    end
end

state=temp;

end


