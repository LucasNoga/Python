function [ state ] = SubBytes( state , W)
%on multiplie chaque élément par A
%puis on xor le state avec C

C='';

A=toeplitz([1 0 0 0 1 1 1 0 0 1 1 1 1 0 0 1] , [ 1 1 0 0 1 1 1 0 0 0 1 1 1 0 0 0]);
c = [1 0 0 1 1 1 0 0 1 0 0 1 1 1 0 0];

for k=1:16
    C=[C,dec2bin(c(1,k))];
end

C=bin2dec(C);

temp = zeros(5,4);


for i=1:5
    for j=1:4
        temp2='';
        if state(i,j) ~= 0
            inverse=recherche_element(state(i,j),W); %inverse : a(i,j)^-1
        else
            inverse=0;
        end
        inverse=dec2bin(inverse,16);
        chaine={inverse(1) inverse(2) inverse(3) inverse(4) inverse(5) inverse(6) inverse(7) inverse(8) inverse(9) inverse(10) inverse(11) inverse(12) inverse(13) inverse(14) inverse(15) inverse(16)}; 
        inverse=[1:16];
        for k = 1:16
            inverse(1,k)=bin2dec(chaine(1,k));
        end
        
        mult=zeros(1,16);

        for l=1:16
            for m=1:16
                mult(1,l)=mult(1,l)+A(l,m)*inverse(1,m);
            end
        end
        
        for k=1:16
            mult(1,k)=mod(mult(1,k),2);
        end
        
        for k = 1:16
            temp2=[temp2,dec2bin(mult(1,k))];
        end
        
        temp2=bin2dec(temp2);
        
        temp(i,j)=bitxor(temp2,C);

    end
end

state=temp;

end


