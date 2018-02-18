function [ state ] = ShiftRows(state)

temp = zeros(5,4);
nbcol=size(state);
nbcol=nbcol(1,2);

for i=1:5
    for j=1:nbcol
        if i==1
            temp(i,j)=state(i,j);
        elseif mod(j+i-1,nbcol) ~= 0
            temp(i,j)=state(i,mod(j+i-1,nbcol));
        else
            temp(i,j)=state(i,mod(j,nbcol)+i-1);
        end
    end
end        

state=temp;

end