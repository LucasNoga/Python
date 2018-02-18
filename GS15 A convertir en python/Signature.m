function [h,r,s] = Signature(HM,x,y,P,g)

fprintf('***************************** \n')
fprintf('*******   Signature   ******* \n')
fprintf('***************************** \n')

gx=feval(symengine,'powermod',g,x,P);
h=feval(symengine,'powermod',gx,1,2);
cle_publique=[P,g,h]

gy=feval(symengine, 'powermod',g,y,P);
r=feval(symengine, 'powermod',gy,1,2); 
R=[1:1];
R=feval(symengine, 'polytodec',r);% r=g^y [P]
inversey=[1:1];
inversey(1,1)=feval(symengine, 'powermod',y,-1,65535);%inverse pour 65535
s=inversey*(HM-x*R);

S=[1:1];
S(1,1)=feval(symengine, 'powermod',s,1,65535); %s = (M-x*k)y^-1 

signature=[R,S]

end
