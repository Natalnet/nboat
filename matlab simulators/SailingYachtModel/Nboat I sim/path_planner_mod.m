%p0 -> lastWaypoint
%p1 -> nextWaypoint
%p -> current position

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

P = [x;y];
if(gnc_par.init == 0)
    gnc_par.p0 = P;
    gnc_par.init = 1;
end

[l, waypoints_size] = size(gnc_par.waypoints);

if(waypoints_size ~= 0)
    if (gnc_par.d_p1 < 95)
        if (gnc_par.isBordejando)
            [l, pontos_bordejar_size] = size(gnc_par.pontos_bordejar);
            if (gnc_par.waypointBId < pontos_bordejar_size)
                gnc_par.p0 = gnc_par.pontos_bordejar(:,gnc_par.waypointBId);
                gnc_par.waypointBId = gnc_par.waypointBId + 1;
                gnc_par.p1 = gnc_par.pontos_bordejar(:,gnc_par.waypointBId);
            else
                gnc_par.isBordejando = false;
                gnc_par.waypointBId = 1;
            end
        else
            gnc_par.p0 = gnc_par.waypoints(:,gnc_par.waypointId);
            gnc_par.waypointId = gnc_par.waypointId + 1;
            if (mod(gnc_par.waypointId,waypoints_size+1) == 0)
                gnc_par.waypointId = 1;
            end
            gnc_par.p1 = gnc_par.waypoints(:,gnc_par.waypointId);                
        end
    else
        if (gnc_par.isBordejando)
            gnc_par.p0 = gnc_par.pontos_bordejar(:,mod(gnc_par.waypointBId,gnc_par.waypointBId-1));
            gnc_par.waypointBId + 1;
            gnc_par.p1 = gnc_par.pontos_bordejar(:,gnc_par.waypointBId);
        else
            gnc_par.p1 = gnc_par.waypoints(:,gnc_par.waypointId);
        end
    end
    
    gnc_par.lastd_p1 = gnc_par.d_p1;
    gnc_par.d_p1 = norm(gnc_par.p1-P)
    gnc_par.d_p1_vec(gnc_par.conte, 1) = gnc_par.d_p1;
    x0 = gnc_par.p0(1);  y0 = gnc_par.p0(2);
    x1 = gnc_par.p1(1);  y1 = gnc_par.p1(2);
    alpha_p = atan2(y1-y0,x1-x0);
    
    verify_movement(P);
    
    %condição para o calcular os pontos de bordejo
    if(rad2deg(abs(alpha_p - alpha_tw + pi)) < 20)
        gnc_par.pontos_bordejar = tack_points([x,y], gnc_par.waypoints(waypointId), d_t, theta_t, alpha_tw);
    end
    waypoint_pair = [gnc_par.p0;gnc_par.p1];
end
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