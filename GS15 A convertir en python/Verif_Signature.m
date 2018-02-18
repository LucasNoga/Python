function [ b] = Verif_Signature(HM,r,s,h,P,g)

fprintf('***************************** \n')
fprintf('****** Vérif_Signature ****** \n')
fprintf('***************************** \n')

R=[1:1];
R=feval(symengine, 'polytodec',r);

hr=feval(symengine, 'powermod',h,R,P); % h^r [P]
hr=feval(symengine, 'powermod',hr,1,2);

S=[1:1];
S(1,1)=feval(symengine, 'powermod',s,1,65535);

rs=feval(symengine, 'powermod',r,S,P); % r^s [P]
hrrs=feval(symengine, 'powermod',rs*hr,1,P); %h^r * r^s[P]
hrrs=feval(symengine, 'powermod',hrrs,1,2);

gHM=feval(symengine, 'powermod',g,HM,P);
gHM=feval(symengine, 'powermod',gHM,1,2);


[hrrs,gHM]

if(hrrs==gHM)
	fprintf('Signature valide \n');
else
    fprintf('Signature non valide \n');
end

end

