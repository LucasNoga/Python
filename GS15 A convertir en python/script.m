clc
clear
close all

%% 
fprintf(' ->1<- \t Super AES \n ->2<- \t Super El-Gamal \n ');
choix_user = input('Choix de l algorithme :\n ');

if choix_user==1
    aes
elseif choix_user==2
    el_gamal
end


