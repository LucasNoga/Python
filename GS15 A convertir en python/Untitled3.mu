
randpol:= proc(p,n)

local P,i,g;

begin

g:=random(0..(p-1));

P:=X^n;

for i from 0 to n-1 do 

P:=P+g()*X^i;

end_for;

P;
end_proc;

randpoly:= proc(p,n)

local P,i,g;

begin

g:=random(0..(p-1));

P:=0;

for i from 0 to n do 

P:=P+g()*X^i;

end_for;

P;
end_proc;

estirreductible:=proc(P,p)

local n,i,s;

begin

n:=degree(P);

s:=X; 

for i from 1 to n-1 do

s:=divide(s^p,P,[X],Rem):
s:=powermod(s,1,2):

if n mod i = 0 then

if s=X then

false

end_if;

end_if; 

end_for;

s:=divide(s^p,P,[X],Rem):
s:=powermod(s,1,2):


bool(s=X);

end_proc;


polirreductible:=proc(T)

local E;

begin

E:=randpol(2,T);

while not estirreductible(E,2) do

E:=randpol(2,T);
end_while;

E;

end_proc;


polyrreductible:=proc(T)

local E;

begin

E:=randpoly(2,T);

while not estirreductible(E,2) do

E:=randpoly(2,T);
end_while;

E;

end_proc;

generateur:=proc(F)

local c1,c2,c3,c4,c5,Q,s;

begin
   s:=0:
   while (s =0) do
    Q:=polyrreductible(15):
    c1:=2^16 - 1;
    c2:=c1/3;
    c3:=c1/5;
    c4:=c1/17;
    c5:=c1/257;
    a:=powermod(Q,c2,F):
    a:=powermod(a,1,2);
    b:=powermod(Q,c3,F):
    b:=powermod(b,1,2);
    c:=powermod(Q,c4,F):
    c:=powermod(c,1,2);
    d:=powermod(Q,c5,F):
    d:=powermod(d,1,2);
    if (a <> 1) and (b <> 1) and (c <> 1) and (d <> 1) then
    s:=1:
    Q;
    else
    s:=0;
    end_if;
end_while;
end_proc;

dectopoly:=proc(coef,i)
  
begin

P:=coef*X^i;

end_proc;

polytodec:=proc(Q)
    local R,i;
begin
    R:=0:
for i from 0 to degree(Q) do
R:=R+(coeff(Q,X,i))*2^i:
end_for;
R;
end_proc;

