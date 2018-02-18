function [ state ] = MixColumns(state_in)

mod_pol = bin2dec ('10000000000101101'); %polynome irreductible 

X=[{'0002' '0004' '0001' '0002' '0002'};...
   {'0002' '0002' '0004' '0001' '0002'};...
   {'0002' '0002' '0002' '0004' '0001'};...
   {'0001' '0002' '0002' '0002' '0004'};...
   {'0004' '0001' '0002' '0002' '0002'}];

for j = 1 : 4
    for i = 1 : 5
        temp = 0;
        for k = 1 : 5
            prod = poly_mult (hex2dec(X(i, k)),state_in(k, j),mod_pol);
            temp = bitxor (temp, prod);
        end
        state(i, j) = temp;
    end
end

end