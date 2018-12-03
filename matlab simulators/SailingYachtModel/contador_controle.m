[l,c] = size(array_controle);
array_controle_teste = array_controle(1,:);
for cont2 = 1:c
    if array_controle_teste(cont2) == 0
        array_controle_teste(cont2) = max(array_controle(1,:));
    end
end
figure;
array_controle_mesh = reshape(array_controle_teste, sqrt(c), sqrt(c));
[x, y] = meshgrid(1:0.5:10.5,1:20);
surf(x, y, -array_controle_mesh);
xlabel('Kp');
ylabel('Ki');
zlabel('-Tempo de chegada');