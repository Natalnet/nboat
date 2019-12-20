[ld, cd] = size(tabela_distancia);
[lt, ct] = size(tabela_tempos);
tabela_controle = zeros(32,2);
distancias = zeros(32,1);
for i = 1:32
    [x, y] = min(tabela_distancia(i,:));
    ditancias(i,1) = x;
    tabela_controle(i,1) = array_kp(i,y);
    tabela_controle(i,2) = array_ki(i,y);
end