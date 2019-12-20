function pontos_bordejar = simular_bordejar(taxa_dist, angulo_bordejo)
close all;
heeling = 0;                %direção do vento referencial de mundo
heading = 0;                %orientação do veleiro
%taxa_dist = 80;             %dt
%angulo_bordejo = 50;        %theta_t
nextLocation = [200; 0];    %destino   
lastLocation = [0; 0];      %inicio

deltaY = nextLocation(2,1) - lastLocation(2,1);
deltaX = nextLocation(1,1) - lastLocation(1,1);
desired_heading = atan2(deltaY,deltaX);

biruta_bord = heeling + heading;

if biruta_bord > (180)
    biruta_bord = biruta_bord - (360);
else if biruta_bord < (-180)
    biruta_bord = biruta_bord + (360);
    end
end

if(abs((biruta_bord)) < 30 && (abs(rad2deg(desired_heading) - heading)) < 20)
        i = 1;

        %Inicio do bordejo
        atual = lastLocation;
        destino =  nextLocation;
        x0 = atual(1,1);
        y0 = atual(2,1);
        x1 = destino(1,1);
        y1 = destino(2,1);           

        distanciaInicial = norm(lastLocation- nextLocation);
        distancia_bordejar =  taxa_dist;

        a_A = (y1 - y0) / (x1 - x0);
        b_A = y0 - (a_A * x0);
%        plot([100 100 0 0], [100 -100 100 -100], '.');
        hold on;
        plot([x0 x1], [y0 y1], 'LineWidth', 2);
        
        if heeling - heading > 0
           angulo_bordejo = -angulo_bordejo;
        end
        
        thetaAB =  angulo_bordejo;
        tan_thetaAB = tand(thetaAB);

        a_B = (a_A - tan_thetaAB) / (tan_thetaAB * a_A + 1);
        b_B = y0 - (a_B * x0);
        plot([x0 50], [y0 a_B*50+b_B], 'r','LineWidth', 2);
        hold on;
        
        teste_ang = atand((a_B - a_A)/(1+(a_A*a_B)));

        d = distanciaInicial;
        
        latBord = x1;
        lonBord = y1;
        
        latFim = x1;
        lonFim = y1;
        latIni = x0;
        lonIni = y0;
        
        dist_bord_max_vet = projecao2d_mod(x1, y1, a_A, b_A ,a_B, b_B);
        dist_bord_max = norm([x1; y1]-dist_bord_max_vet);
        
        if distancia_bordejar > dist_bord_max
            distancia_bordejar = dist_bord_max;
        end
        
        while (abs(d - distancia_bordejar) > 1)
            latMedia = (latFim + latIni) / 2;
            lonMedia = (lonFim + lonIni) / 2;
            
            ponto_medio_A(1,1) = latMedia;
            ponto_medio_A(2,1) = lonMedia;
            
            pontoProj = projecao2d_mod(latMedia, lonMedia, a_A, b_A ,a_B, b_B);
%             pontoProj = projecao2d(latMedia, lonMedia, a_B, b_B);
            plot(pontoProj(1,1), pontoProj(2,1), '.','LineWidth', 2);

            d = norm(ponto_medio_A-pontoProj);
            
            if d > distancia_bordejar
                latFim = latMedia;
                lonFim = lonMedia;
            elseif d < distancia_bordejar
                latIni = latMedia;
                lonIni = lonMedia;
            end

            latBord = latMedia;
            lonBord = lonMedia;
        end

        ponto_projetado(1,1) = latBord;
        ponto_projetado(2,1) = lonBord;

        latProj = pontoProj(1,1);
        lonProj = pontoProj(2,1);

        p0m = projecao2d(latProj, lonProj, a_A, b_A);

        d_p0 = norm(p0m-atual);
        pontos_bordejar(:, i) = [latProj;lonProj];

        i =  i + 1;

        b_linha1 = -a_A *  pontos_bordejar(1,1) +  pontos_bordejar(2,1);

        if(b_linha1 > b_A)
            b_linha2 = b_A - (b_linha1 - b_A);
        else
            b_linha2 = b_A + (b_A - b_linha1);
        end

        num_pontos = floor(norm(atual-destino)/d_p0);

        delta_x = p0m(1,1) - x0;
        delta_y = p0m(2,1) - y0;

        tt_x = x0 + delta_x;
        tt_y = y0 + delta_y;

        p0l1 = projecao2d(p0m(1,1), p0m(2,1), a_A, b_linha1);
        p0l2 = projecao2d(p0m(1,1), p0m(2,1), a_A, b_linha2);

        bom = 1;
        ruim = 1;

        for z = 1:num_pontos
            delta_x_temp = z * delta_x;
            delta_y_temp = z * delta_y;

            if mod(z,2) == 0
                controle_loc(1,1) = p0l1(1,1) + delta_x_temp;
                controle_loc(2,1) = p0l1(2,1) + delta_y_temp;
                pontos_bordejar(:, i) = controle_loc;
                i =  i + 1;
                bom = z;
            else
                aux = abs(heeling - abs(desired_heading));
                %aux = rad2deg(aux);
                delta_xaux = aux * delta_x/31;
                delta_yaux = aux * delta_y/31;
                controle_loc(1,1) = p0l2(1,1) + delta_x_temp - delta_xaux;
                controle_loc(2,1) = p0l2(2,1) + delta_y_temp - delta_yaux;
                pontos_bordejar(:, i) = controle_loc;
                i =  i + 1;
                ruim = z;
            end
        end

        if(((heeling - desired_heading) > 0) && (rad2deg(heeling - desired_heading) < 6))
            bom = ruim; 
        end
        
        [l,c] = size(pontos_bordejar);
        d_p0_pu = norm(atual-pontos_bordejar(:,c)); %distancia de p0 a pu
        d_p0_pd = norm(atual-destino); %distancia de p0 a pd
        if d_p0_pu > d_p0_pd
            pontos_bordejar(:,c) = destino;
        end

%         [l,c] = size( pontos_bordejar);
%         if(angulo_bordejo >= 40)
%             last = c;
%             if last-1 == 0
%                 ant = last;
%             else
%                 ant = last-1;
%             end         
%             dist_dest = norm( pontos_bordejar(:,ant)-destino);
%             dist_ant = norm( pontos_bordejar(:,last)- pontos_bordejar(:,ant));
%             if(dist_dest < dist_ant)
%                  pontos_bordejar(:,last) = destino;
%             else
%                  pontos_bordejar(:, i) = destino;
%                  i =  i + 1;
%             end
%         else
%              pontos_bordejar(:, i) = destino;
%              i =  i + 1;
%         end
        %[l,c] = size( pontos_bordejar);
        %pontos_bordejar(:, i) = destino;
        hold on;
        set(gca, 'FontSize', 14, 'LineWidth', 1);
        plot(lastLocation(1,1), lastLocation(2,1), '-go' ,'LineWidth', 1.5);
        plot(nextLocation(1,1), nextLocation(2,1), '-ro' ,'LineWidth', 1.5);

        [l,c] = size(pontos_bordejar);
        pbstst = zeros(l,c+1);
        pbstst(:,2:c+1) = pontos_bordejar(:,1:c);
        [lpb, cpb] = size(pbstst);
            for contPlot = 2:cpb
               plot(pbstst(1,contPlot),pbstst(2,contPlot) ,'ko', 'LineWidth', 2); 
            end
end
end

function ponto=projecao2d_mod(lat, lon, a, b, a_p, b_p)
if a == 0
    a = 0.000000001;
end
if b == 0
    b = 0.000000001;
end
    a_aux = -1/a;
    b_aux = -a_aux * lat + lon;
    %plot(a_aux*[0:0.1:10]+b_aux, 'LineWidth', 2);
    
    ponto(1,1) = (b_aux - b_p) / (a_p - a_aux);
    ponto(2,1) =  a_p * ponto(1,1) + b_p;
end

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