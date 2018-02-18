function [ state ] = InvMixColumns(state_in)

mod_pol = bin2dec ('10000000000101101'); %polynome irréductible X^16+X^5+X^3+X^2+1

X=[{'0002' '0004' '0001' '0002' '0002'};...
          {'0002' '0002' '0004' '0001' '0002'};...
          {'0002' '0002' '0002' '0004' '0001'};...
          {'0001' '0002' '0002' '0002' '0004'};...
          {'0004' '0001' '0002' '0002' '0002'}];
Xprim=[{'51EB' '3ABE' '8F02' 'D5DC' '8741'};...
       {'8741' '51EB' '3ABE' '8F02' 'D5DC'};...
       {'D5DC' '8741' '51EB' '3ABE' '8F02'};...
       {'8F02' 'D5DC' '8741' '51EB' '3ABE'};...
       {'3ABE' '8F02' 'D5DC' '8741' '51EB'}];

for j = 1 : 4 %colonne
    for i = 1 : 5 %ligne
        temp = 0;
        for k = 1 : 5
            prod = poly_mult (hex2dec(Xprim(i, k)),state_in(k, j),mod_pol);%multiplier Xprim avec le state modulu polynome
            temp = bitxor (temp, prod);
        end
        state(i, j) = temp;
    end
end

end