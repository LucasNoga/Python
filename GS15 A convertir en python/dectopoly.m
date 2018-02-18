function [ out ] = dectopoly( in )
%permet de convertir un décimal sous forme polynomiale

        in=dec2bin(in,16);
        tab_coeff={in(1) in(2) in(3) in(4) in(5) in(6) in(7) in(8) in(9) in(10) in(11) in(12) in(13) in(14) in(15) in(16)};

        for k=1:16
            coeff(1,k)=bin2dec(tab_coeff(17-k));
        end

        in=sym('0');

        for k=0:15
            in=in+feval(symengine,'dectopoly',coeff(1,k+1),k);
        end
        
        out=in;

end

