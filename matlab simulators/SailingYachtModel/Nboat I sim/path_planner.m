function desired_heading=path_planner(V_in)
global par

x = V_in(1);
y = V_in(2);
phi = V_in(3); %roll
par.psi = V_in(4); %yaw
u = V_in(5);
v = V_in(6);
p = V_in(7);
r = V_in(8);
par.taxa_dist = V_in(9);
par.angulo_bordejo = V_in(10);
wind_angle = V_in(11);
vt = V_in(12);
water_angle =  V_in(13);
water_spd =  V_in(14);
[l,c] = size(V_in);
index = 1;
for i = 15:2:l-1
    par.waypoints(1,index) = V_in(i);
    par.waypoints(2,index) = V_in(i+1);
    index = index + 1;
end

pontoProj = [0;0];
destino = [0;0];

lastLocation = [x;y];
% desired_heading = 0;

par.velocidade(par.contVel) = sqrt(u^2 + v^2);
par.contVel = par.contVel + 1;
%plot(par.velocidade, 'r');
%hold on;

[l, waypoints_size] = size(par.waypoints);
    if(waypoints_size ~= 0)
        if (par.distanciaAlvo < 3)
            if (par.isBordejando)
                [l, pontos_bordejar_size] = size(par.pontos_bordejar);
                if (par.waypointBId < pontos_bordejar_size)
                    par.waypointBId = par.waypointBId + 1;
                    par.nextLocation = par.pontos_bordejar(:,par.waypointBId);
                else
                    par.isBordejando = false;
                    par.waypointBId = 1;
                end
            else
                set_param('sailboatModel', 'SimulationCommand' ,'stop');
                par.waypointId = par.waypointId + 1;
                if (mod(par.waypointId,waypoints_size+1) == 0)
                    par.waypointId = 1;
                    teste_bord = 1;
                end
%                 set_param('sailboatModel', 'SimulationCommand' ,'stop');
                par.nextLocation = par.waypoints(:,par.waypointId);                
            end
        else
            if (par.isBordejando)
                par.nextLocation = par.pontos_bordejar(:,par.waypointBId);
            else
                par.nextLocation = par.waypoints(:,par.waypointId);
            end
        end
        
        if(par.controle == 0)
            par.lastlastLocation = lastLocation;
            distanciaInicial = norm(lastLocation-par.nextLocation);
            par.controle = 1;
        end
        par.lastDistanciaAlvo = par.distanciaAlvo;
        par.distanciaAlvo = norm(lastLocation-par.nextLocation);
        
        if par.distanciaAlvo >= par.lastDistanciaAlvo
            par.contador_bug = par.contador_bug + 1;
        else
            par.contador_bug = 0;
        end
        
        if par.contador_bug > 300
            set_param('sailboatModel', 'SimulationCommand' ,'stop');
            par.flag = 1;
        end
        
        heeling = pi + wind_angle;
        
        if heeling > pi
            heeling = heeling - 2*pi;
        end
        if heeling < -pi
            heeling = heeling + 2*pi;
        end

        biruta = heeling - par.psi;
        
%         if biruta > pi
%             biruta = biruta - pi;
%         else
%             biruta = biruta + pi;
%         end
        
        if(biruta < 0)
            biruta_s = -biruta;
        else
            biruta_s = biruta;
        end

        if biruta_s < deg2rad(10)
            sail_angle = pi/2;
        else
            sail_angle = (pi/2) * (biruta_s)/pi;
        end

% sail_angle = (pi/2) * (biruta_s)/pi;
        
        if(sail_angle > 1.5708)
            sail_angle = 1.5708;
        end
        if(sail_angle < 0)
            sail_angle = 0;
        end            
        
        deltaY = par.nextLocation(2,1) - lastLocation(2,1);
        deltaX = par.nextLocation(1,1) - lastLocation(1,1);
        desired_heading = atan2(deltaY,deltaX);
        
        teste1 = abs(rad2deg(biruta));
        teste2 = rad2deg(abs(desired_heading - par.psi));
        teste3 = rad2deg(heeling - desired_heading);
        
        par.spvec(par.spveccont) = (pi - (desired_heading - par.psi))/pi;
        if par.spvec(par.spveccont) <= 1.02 && par.spvec(par.spveccont) >= 0.98 && ~par.flagAcomod
            par.tempoDeAcomod2 = get_param('sailboatModel','SimulationTime');
            teste = get_param('sailboatModel','SimulationTime');
            par.flagAcomod = true;
        else if ~(par.spvec(par.spveccont) <= 1.02 && par.spvec(par.spveccont) >= 0.98)
                par.flagAcomod = false;
            end
        end
        
        if par.spvec(par.spveccont) > par.overshoot
            par.overshoot = par.spvec(par.spveccont);
            par.tempopico = get_param('sailboatModel','SimulationTime');
        end
        
        if par.flagtemposub && par.spvec(par.spveccont) > 1
            par.flagtemposub = false;
        end
        
        if par.flagtemposub && par.spvec(par.spveccont) <= 1
            par.temposub = get_param('sailboatModel','SimulationTime');
        end
        
        par.spveccont = par.spveccont + 1;
        
        if biruta > (pi)
            biruta_bord = biruta - (2*pi);
        else if biruta < (-pi)
            biruta_bord = biruta + (2*pi);
        else
            biruta_bord = biruta;
            end
        end
        
        if desired_heading > (pi)
            desired_heading_bord = desired_heading - (2*pi);
        else if desired_heading < (-pi)
            desired_heading_bord = desired_heading + (2*pi);
        else
            desired_heading_bord = desired_heading;
            end
        end
        
        if par.psi > (pi)
            psi_bord = par.psi - (2*pi);
        else if par.psi < (-pi)
            psi_bord = par.psi + (2*pi);
        else
            psi_bord = par.psi;
            end
        end
        
        if(abs(rad2deg(biruta_bord)) < 40 && ~par.isBordejando && rad2deg(abs(desired_heading_bord - psi_bord)) < 20)
        %if(abs(rad2deg(heeling - desired_heading)) < 30  && ~par.isBordejando)
            par.i = 1;
            par.isBordejando = true;

            %Inicio do bordejo
            atual = lastLocation;
            destino = par.nextLocation;
            x0 = atual(1,1);
            y0 = atual(2,1);
            x1 = destino(1,1);
            y1 = destino(2,1);           

            distanciaInicial = norm(lastLocation-par.nextLocation);
            %distancia_bordejar = par.taxa_dist * distanciaInicial;
            distancia_bordejar = par.taxa_dist;

            a_A = (y1 - y0) / (x1 - x0);
            b_A = y0 - (a_A * x0);

%             thetaAB = abs(rad2deg(biruta)) - par.angulo_bordejo;
%             teste = rad2deg(thetaAB);
            thetaAB = par.angulo_bordejo;
            tan_thetaAB = tand(thetaAB);
            
            if(heeling - desired_heading > 0)
                a_B = (-a_A + tan_thetaAB) / (-tan_thetaAB * a_A - 1);     
            else
                a_B = (-a_A - tan_thetaAB) / (tan_thetaAB * a_A - 1);      
            end
            b_B = y0 - (a_B * x0);

            d = distanciaInicial;
            d_p0 = 999999999;
            
            latBord = x1;
            lonBord = y1;

            while (d > distancia_bordejar)
                latMedia = (latBord + x0) / 2;
                lonMedia = (lonBord + y0) / 2;

                ponto_medio_A(1,1) = latMedia;
                ponto_medio_A(2,1) = lonMedia;

                pontoProj = projecao2d_mod(latMedia, lonMedia, a_A, b_A, a_B, b_B);

                d = norm(ponto_medio_A-pontoProj);

                latBord = latMedia;
                lonBord = lonMedia;
            end

            ponto_projetado(1,1) = latBord;
            ponto_projetado(2,1) = lonBord;

            latProj = pontoProj(1,1);
            lonProj = pontoProj(2,1);
            
            p0m = projecao2d(latProj, lonProj, a_A, b_A);

            d_p0 = norm(p0m-atual);
            par.pontos_bordejar(:,par.i) = [latProj;lonProj];
            
            par.i = par.i + 1;

            b_linha1 = -a_A * par.pontos_bordejar(1,1) + par.pontos_bordejar(2,1);

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

            for z = 1:num_pontos-1
                delta_x_temp = z * delta_x;
                delta_y_temp = z * delta_y;

                if mod(z,2) == 0
                    controle_loc(1,1) = p0l1(1,1) + delta_x_temp;
                    controle_loc(2,1) = p0l1(2,1) + delta_y_temp;
                    par.pontos_bordejar(:,par.i) = controle_loc;
                    par.i = par.i + 1;
                    bom = z;
                else
                    aux = abs(heeling - abs(desired_heading));
                    aux = rad2deg(aux);
                    delta_xaux = aux * delta_x/31;
                    delta_yaux = aux * delta_y/31;
                    controle_loc(1,1) = p0l2(1,1) + delta_x_temp - delta_xaux;
                    controle_loc(2,1) = p0l2(2,1) + delta_y_temp - delta_yaux;
                    par.pontos_bordejar(:,par.i) = controle_loc;
                    par.i = par.i + 1;
                    ruim = z;
                end
            end
            
%             if(((heeling - desired_heading) > 0) && (rad2deg(heeling - desired_heading) < 6))
%                 bom = ruim; 
%             end
            [l,c] = size(par.pontos_bordejar);
            teste_show = get_param('sailboatModel/path planner/tack angle', 'Value');
            %if(str2num(teste_show) >= 40)
            if(1)
                last = c;
                if last-1 == 0
                    ant = last;
                else
                    ant = last-1;
                end         
                dist_dest = norm(par.pontos_bordejar(:,ant)-destino);
                dist_ant = norm(par.pontos_bordejar(:,last)-par.pontos_bordejar(:,ant));
                if(dist_dest < dist_ant)
                    par.pontos_bordejar(:,last) = destino;
                else
                    par.pontos_bordejar(:,par.i) = destino;
                    par.i = par.i + 1;
                end
            else
                par.pontos_bordejar(:,par.i) = destino;
                par.i = par.i + 1;
             end
            %fim do bordejar
            %[l,c] = size(par.pontos_bordejar);
            %par.pontos_bordejar(:,c+1) = destino;
        end
        
%         if mod(par.contador_teste, 100) == 0
%             %set_param('sailboatModel', 'SimulationCommand' ,'pause');
%             close all;
%             hold on;
%             plot(V_in2(2), V_in2(1),'r', 'LineWidth', 1.5);
%             % [l,c] = size(par.pontos_bordejar);
%             % pbstst = zeros(l,c+1);
%             % pbstst(:,2:c+1) = par.pontos_bordejar(:,1:c);
%             % [lpb, cpb] = size(pbstst);
%             % for contPlot = 2:cpb-1
%             %    plot(pbstst(2,contPlot), pbstst(1,contPlot), 'blacko', 'LineWidth', 2); 
%             % end
%             plot(0,0, 'black.', 'MarkerSize', 14, 'LineWidth', 1.5);
%             plot(0,100, 'blackx', 'MarkerSize', 8, 'LineWidth', 1.5);
%             plot(50,50, 'blackx', 'MarkerSize', 8, 'LineWidth', 1.5);
%             axis tight;
%             % [l,c] = size(X.time);
%             % tempos(i) = X.time(l,1);
%             grid;
%             xlabel('x[m]');
%             ylabel('y[m]');
%             %hold off;
%             %set_param('sailboatModel', 'SimulationCommand' ,'continue');
%             par.contador_teste = 1;
%         else
%             par.contador_teste = par.contador_teste + 1;
%         end
        
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