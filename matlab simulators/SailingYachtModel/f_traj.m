function desired_heading=f_traj(V_in2)
global par

x = V_in2(1);
y = V_in2(2);
phi = V_in2(3);
par.psi = V_in2(4);
u = V_in2(5);
v = V_in2(6);
p = V_in2(7);
r = V_in2(8);

lastLocation = [x;y];
% desired_heading = 0;

[l, c] = size(par.waypoints);
if(c ~= 0)
    if (par.distanciaAlvo < 10)
        if (par.isBordejando)
            [l, c] = size(pontos_bordejar);
            if (par.waypointBId < c)
                par.waypointBId = par.waypointBId + 1;
                nextLocation = pontos_bordejar(:,waypointBId);
            else
                par.isBordejando = false;
                par.waypointBId = 1;
            end
        else
            [l,c] = size(par.waypoints);
            par.waypointId = par.waypointId + 1;
            if (mod(par.waypointId,c+1) == 0)
                par.waypointId = 1;
            end
            nextLocation = par.waypoints(:,par.waypointId);
        end
    else
        if (par.isBordejando)
            nextLocation = par.pontos_bordejar(:,par.waypointBId);
        else
            nextLocation = par.waypoints(:,par.waypointId);
        end
    end
    if(par.controle == 0)
        lastlastLocation = lastLocation;
        distanciaInicial = norm(lastLocation-nextLocation);
    end
    par.distanciaAlvo = norm(lastLocation-nextLocation);
end

biruta = par.alpha_w - par.psi;
deltaY = nextLocation(2,1) - lastLocation(2,1);
deltaX = nextLocation(1,1) - lastLocation(1,1);
desired_heading = atan2(deltaY,deltaX);

if(abs(biruta) < 30 && ~par.isBordejando)
    par.isBordejando = true;
    %Inicio do bordejo
    atual = lastLocation;
    destino = nextLocation;
    x0 = atual(1,1);
    y0 = atual(2,1);
    x1 = destino(1,1);
    y1 = destino(2,1);
    
    distancia_bordejar = taxa_dist * distanciaInicial;

    a_A = (y1 - y0) / (x1 - x0);
    b_A = y0 - (a_A * x0);

    thetaAB = abs(saturador(biruta)) - (angulo_bordejo*pi/180);
    tan_thetaAB = tan(thetaAB);
    if(par.alpha_w - desired_heading > 0)
        a_B = (-a_A - tan_thetaAB) / (tan_thetaAB * a_A - 1);      
    else
        a_B = (-a_A + tan_thetaAB) / (-tan_thetaAB * a_A - 1);      
    end
    b_B = y0 - (a_B * x0);
    
    d = distanciaInicial;
    d_p0 = 999999999;
    
    latBord = x1;
    lonBord = y1;
    latProj = x1;
    lonProj = y1;
    
    while (d > distancia_bordejar)
        latMedia = (latBord + x0) / 2;
        lonMedia = (lonBord + y0) / 2;
        
        ponto_medio_A(1,1) = latMedia;
        ponto_medio_A(2,1) = lonMedia;
        
        pontoProj = projecao2d_mod(latMedia, lonMedia, a_A, b_A, a_B, b_B);
        
        d = norm(ponto_medio-pontoProj);
        
        latBord = latMedia;
        lonBord = lonMedia;
    end
    
    ponto_projetado(1,1) = latBord;
    ponto_projetado(2,1) = lonBord;
    
    p0m = projecao2d(pontoProj(1,1), pontoProj(2,1), a_A, b_A);
    
    d_p0 = norm(p0m-atual);
    pontos_bordejar(:,par.i) = [latProj;lonProj];
    par.i = par.i + 1;
    
    b_linha1 = -a_A * pontos_bordejar(1,1) + pontos_bordejar(2,1);
    
    if(b_linha1 > b_A)
        b_linha2 = b_A - (b_linha1 - b_A);
    else
        b_linha2 = b_A - (b_A - b_linha1);
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
    
    for z = 1:(num_pontos-1)
        delta_x_temp = z * delta_x;
        delta_y_temp = z * delta_y;
        
        if mod(z,2) == 0
            controle_loc(1,1) = p0l1(1,1) + delta_x_temp;
            controle_loc(2,1) = p0l1(2,1) + delta_y_temp;
            pontos_bordejar(:,par.i) = controle_loc;
            par.i = par.i + 1;
            bom = z;
        else
            aux = abs(par.alpha_w - abs(desired_heading));
            delta_xaux = aux * delta_x/31;
            delta_yaux = aux * delta_y/31;
            controle_loc(1,1) = p0l2(1,1) + delta_x_temp - delta_xaux;
            controle_loc(2,1) = p0l2(2,1) + delta_y_temp - delta_yaux;
            pontos_bordejar(:,par.i) = controle_loc;
            par.i = par.i + 1;
            ruim = z;
        end
    end
    if(((par.alpha_w - desired_heading) > 0) && ((par.alpha_w - desired_heading) < 6))
        bom = ruim; 
    end
    [l,c] = size(pontos_bordejar)
    if(c-1 == bom)
        last = c-1;
        ant = last-1;
        dist_dest = norm(pontos_bordejar(:,ant)-destino);
        dist_ant = norm(pontos_bordejar(:,last)-pontos_bordejar(:,ant));
        if(dist_dest < dist_ant)
            pontos_bordejar(:,last) = destino;
        end
    else
        pontos_bordejar(:,par.i) = destino;
        par.i = par.i + 1;
    end
    %fim do bordejar
end
end

function ponto=projecao2d_mod(lat, lon, a, b, a_p, b_p)
    a_aux = -1/a;
    b_aux = -a_aux * lat + lon;
    
    ponto(1,1) = (b_aux - b_p) / (a_p - a_aux);
    ponto(2,1) =  a_p * ponto(1,1) + b_p;
end

function ponto= projecao2d(lat, lon, a, b)
    a_aux = -1/a;
    b_aux = -a_aux * lat + lon;
    
    ponto(1,1) = (b_aux - b) / (a - a_aux);
    ponto(2,1) =  a * ponto(1,1) + b;
end

