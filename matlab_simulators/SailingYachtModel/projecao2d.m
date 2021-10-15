function ponto= projecao2d(lat, lon, a, b)
if a == 0
    a = 0.000000001;
end
if b == 0
    b = 0.000000001;
end
    a_aux = -1/a;
    b_aux = -a_aux * lat + lon;
    
    ponto(1,1) = (b_aux - b) / (a - a_aux);
    ponto(2,1) =  a * ponto(1,1) + b;
end