[l,c] = size(array_distance);
array_dist_teste = array_distance(1,:);
for cont2 = 1:c
    if array_dist_teste(cont2) == 0
        array_dist_teste(cont2) = max(array_distance(1,:));
    end
end
figure;
array_dist_mesh = reshape(array_dist_teste, sqrt(c), sqrt(c));
[x, y] = meshgrid(1:0.5:10.5,1:20);
surf(x, y, -array_dist_mesh);
xlabel('Kp');
ylabel('Ki');
zlabel('-Distância lateral');