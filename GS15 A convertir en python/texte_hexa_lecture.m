function [ texte_clair_hexa ] = texte_hexa_lecture(path,B)

%Initialisation

fid = fopen(path);
texte_clair = fread(fid);
fclose(fid);

texte_clair_bin = dec2bin(texte_clair,8);
% S'assurer que le texte contient un nombre de bits multiple de B (notamment pour le fichier Ã  chiffrer).
texte_clair_bin = texte_clair_bin';
texte_clair_bin = texte_clair_bin(:);
% On rajoute des 0 pour lire le texte en son entier 

while mod(numel(texte_clair_bin),B) ~= 0
    texte_clair_bin(numel(texte_clair_bin)+1)='0';
end

texte_clair_bin = texte_clair_bin(1:end);

texte_clair_hexa = reshape(texte_clair_bin, B , [])';
texte_clair_hexa = bin2dec(texte_clair_hexa);

%texte_clair_hexa = dec2hex(uint16(texte_clair_hexa));

% Le résultat est retourné sous la forme d'un vecteur 'colonne' 
%dont chaque élément est compris entre 0 et 65535.

end
