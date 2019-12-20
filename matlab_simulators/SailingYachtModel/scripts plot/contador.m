[l,c] = size(array_temp);
array_temp_teste = array_temp(30,:);
for cont2 = 1:c
    if array_temp_teste(cont2) == 0
        array_temp_teste(cont2) = max(array_temp_teste);
    end
end
figure;
array_temp_mesh = reshape(array_temp_teste, sqrt(c), sqrt(c));
%[x, y] = meshgrid(0.1:0.8/30:0.9,20:60/30:80);
[x, y] = meshgrid(1:0.5:10.5,1:20);
surf(x, y, -array_temp_mesh);
set(gca, 'FontSize', 16, 'LineWidth', 1);
xlabel('Kp');
ylabel('Ki');
zlabel('-Distância lateral');