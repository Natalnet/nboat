resultados = zeros(10,4);
for i=1:10
    resultados(i,:) = otimizarBordejar(10,20,10);
end
cd caso3
save resultados
cd ..