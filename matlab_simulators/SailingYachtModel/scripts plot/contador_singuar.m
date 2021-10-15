[l,c] = size(array_tempo);
array_tempo_teste = array_tempo;
for cont1 = 1:1
    for cont2 = 1:c
            if array_tempo_teste(cont1, cont2) == 0
                array_tempo_teste(cont1, cont2) = max(array_tempo_teste(cont1,:));
            end
    end
    figure;
    array_tempo_mesh = reshape(array_tempo_teste(cont1,:), sqrt(c), sqrt(c));
    [x, y] = meshgrid(0.1:0.8/30:0.9,20:60/30:80);
    surf(x, y, -array_tempo_mesh);
    set(gca,'fontsize',16);
    xlabel('Distância de bordejo (m)');
    ylabel('Ângulo de bordejo (graus)');
    zlabel('-Tempo de chegada (s)');
end