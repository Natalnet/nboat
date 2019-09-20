%p0 -> lastWaypoint
%p1 -> nextWaypoint
%p -> current position

%gerenciador dos waypoints. a cada iteração verifica se é preciso tack
%(principal função). A saída é o próximo par de waypoints que o seguidor de
%linha deve seguir.

function waypoint_pair=path_planner_mod(V_in)
global gnc_par
global mdl_par

%sailboat state
x = V_in(1);
y = V_in(2);
phi = V_in(3);
psi = V_in(4);
u = V_in(5);
v = V_in(6);
p = V_in(7);
r = V_in(8);

d_t = V_in(9);
theta_t = V_in(10);

alpha_tw = V_in(11);
gamma_tw = alpha_tw;
V_tw = V_in(12);
alpha_tc =  V_in(13);
V_tc =  V_in(14);

[l,c] = size(V_in);
j = 1;
for i= 15:2:l
    gnc_par.waypoints(1,j) = V_in(i);
    gnc_par.waypoints(2,j) = V_in(i+1);
    j = j + 1;
end

% gnc_par.waypoints = gnc_par.waypoints';

P = [x;y];
% if(gnc_par.init == 0)
%     gnc_par.p0 = P;
%     gnc_par.init = 1;
% end

[l, waypoints_size] = size(gnc_par.waypoints);

if ~gnc_par.isBordejando
    waypoint_pair = gnc_par.waypoints(:);
else
    [l, pb_size] = size(gnc_par.pontos_bordejar);
    %distancia entre o ponto atual e o proximo waypoint
    dist = norm(P - gnc_par.pontos_bordejar(gnc_par.waypointBId,:)');
    %se tiver alcançado o ponto
    if dist < 5
        %se ainda tem pontos, passa para o proximo
        if (gnc_par.waypointBId < l)
            gnc_par.waypointBId = gnc_par.waypointBId + 1;
        %senão, para o bordejar
        else
            gnc_par.isBordejando = false;
            gnc_par.waypointBId = 1;
        end
    end
    waypoint_pair(1,:) = gnc_par.pontos_bordejar(gnc_par.waypointBId-1,:);
    waypoint_pair(2,:) = gnc_par.pontos_bordejar(gnc_par.waypointBId,:);
    waypoint_pair = waypoint_pair';
    waypoint_pair = waypoint_pair(:);
end

gamma_tw = gamma_tw - pi;
gamma_tw = constrain(gamma_tw);
%angulo de ataque do vento com o veleiro
alpha = psi - gamma_tw;
alpha = constrain(alpha);

%Verifica se há a necessidade de tack
if(abs(alpha) < 30 && ~gnc_par.isBordejando)
    gnc_par.pontos_bordejar = tack_points(gnc_par.waypoints(:,1), gnc_par.waypoints(:,2), d_t, theta_t, alpha_tw);
    [l, c] = size(gnc_par.pontos_bordejar);
    aux(1,1) = waypoint_pair(1);
    aux(1,2) = waypoint_pair(2);
    aux = [aux;gnc_par.pontos_bordejar];
    aux(l+2,1) = waypoint_pair(3);
    aux(l+2,2) = waypoint_pair(4);
    gnc_par.pontos_bordejar = aux;
end

%calc velocity
U = sqrt(u^2 + v^2);
x1 = gnc_par.waypoints(1,1);
y1 = gnc_par.waypoints(2,1);
x2 = gnc_par.waypoints(1,2);
y2 = gnc_par.waypoints(2,2);

d_x = x2 - x1;
d_y = y2 - y1;
alpha_k = atan2(d_y,d_x);

if U == 0
    beta = 0;
else
   beta = asin(v/U); 
end

course = psi + beta;

gnc_par.Vd(gnc_par.Vd_count, 1) = U*cos(alpha_k - course);
gnc_par.Vd_count = gnc_par.Vd_count + 1;


% if(waypoints_size ~= 0)
%     %se proximo do ponto: muda para o proximo waypoint
%     if (gnc_par.d_p1 < 5)
%         %se estiver no meio do tack seleciona waypoint do vetor de tack
%         if (gnc_par.isBordejando)
%             [l, pontos_bordejar_size] = size(gnc_par.pontos_bordejar);
%             if (gnc_par.waypointBId < pontos_bordejar_size)
%                 gnc_par.p0 = gnc_par.pontos_bordejar(:,gnc_par.waypointBId);
%                 gnc_par.waypointBId = gnc_par.waypointBId + 1;
%                 gnc_par.p1 = gnc_par.pontos_bordejar(:,gnc_par.waypointBId);
%             else
%                 gnc_par.isBordejando = false;
%                 gnc_par.waypointBId = 1;
%             end
%         %senão, seleciona waypoint do vetor de waypoints
%         else
%             gnc_par.p0 = gnc_par.waypoints(:,gnc_par.waypointId);
%             gnc_par.waypointId = gnc_par.waypointId + 1;
%             %deixa Ids circulares
%             if (mod(gnc_par.waypointId,waypoints_size+1) == 0)
%                 gnc_par.waypointId = 1;
%             end
%             gnc_par.p1 = gnc_par.waypoints(:,gnc_par.waypointId);                
%         end
%     %se não estiver perto do waypoint destino...
%     else
%         if (gnc_par.isBordejando)
%             gnc_par.p0 = gnc_par.pontos_bordejar(:,mod(gnc_par.waypointBId,gnc_par.waypointBId-1));
%             gnc_par.waypointBId + 1;
%             gnc_par.p1 = gnc_par.pontos_bordejar(:,gnc_par.waypointBId);
%         else
%             gnc_par.p1 = gnc_par.waypoints(:,gnc_par.waypointId);
%         end
%     end
%     
%     gnc_par.lastd_p1 = gnc_par.d_p1;
%     gnc_par.d_p1 = norm(gnc_par.p1-P);
%     gnc_par.d_p1_vec(gnc_par.conte, 1) = gnc_par.d_p1;
%     x0 = gnc_par.p0(1);  y0 = gnc_par.p0(2);
%     x1 = gnc_par.p1(1);  y1 = gnc_par.p1(2);
%     alpha_p = atan2(y1-y0,x1-x0);
%     
%     verify_movement(P);
%     
%     %condição para o calcular os pontos de bordejo
% %     if(rad2deg(abs(alpha_p - alpha_tw + pi)) < 20)
% %         gnc_par.pontos_bordejar = tack_points([x,y], gnc_par.waypoints(waypointId), d_t, theta_t, alpha_tw);
% %     end
%     waypoint_pair = [gnc_par.p0;gnc_par.p1];
% end
end

function record_control()
global gnc_par

    gnc_par.spvec(gnc_par.spveccont) = (pi - (desired_heading - gnc_par.psi))/pi;
    if gnc_par.spvec(gnc_par.spveccont) <= 1.02 && gnc_par.spvec(gnc_par.spveccont) >= 0.98 && ~gnc_par.flagAcomod
        gnc_par.tempoDeAcomod2 = get_param('sailboatModel','SimulationTime');
        gnc_par.flagAcomod = true;
    else if ~(gnc_par.spvec(gnc_par.spveccont) <= 1.02 && gnc_par.spvec(gnc_par.spveccont) >= 0.98)
            gnc_par.flagAcomod = false;
        end
    end

    if gnc_par.spvec(gnc_par.spveccont) > gnc_par.overshoot
        gnc_par.overshoot = gnc_par.spvec(gnc_par.spveccont);
        gnc_par.tempopico = get_param('sailboatModel','SimulationTime');
    end

    if gnc_par.flagtemposub && gnc_par.spvec(gnc_par.spveccont) > 1
        gnc_par.flagtemposub = false;
    end

    if gnc_par.flagtemposub && gnc_par.spvec(gnc_par.spveccont) <= 1
        gnc_par.temposub = get_param('sailboatModel','SimulationTime');
    end

    gnc_par.spveccont = gnc_par.spveccont + 1;
end

function verify_movement(P)
    global gnc_par
    gnc_par.last_d_p1 = gnc_par.d_p1;
    gnc_par.d_p1 = norm(P-gnc_par.p1);

    if gnc_par.d_p1 >= gnc_par.lastd_p1
        gnc_par.contador_bug = gnc_par.contador_bug + 1;
    else
        gnc_par.contador_bug = 0;
    end

    if gnc_par.contador_bug > 300
        set_param('sailboatModel', 'SimulationCommand' ,'stop');
        gnc_par.flag = 1;
    end
end