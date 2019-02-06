%p0 -> lastWaypoint
%p1 -> nextWaypoint
%p -> current position

function desired_heading=path_planner_mod(V_in)
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

alpha_aw = mdl_par.alpha_aw;

p = [x;y];

[l, waypoints_size] = size(gnc_par.waypoints);

if(waypoints_size ~= 0)
    if (gnc_par.d_p1 < 5)
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
            gnc_par.p1 = gnc_par.pontos_bordejar(:,gnc_par.waypointBId);
        else
            gnc_par.p1 = gnc_par.waypoints(:,gnc_par.waypointId);
        end
    end
    
    verify_movement();
    
    %condição para o calcular os pontos de bordejo
    if(rad2deg(abs(psi_d - alpha_tw + pi)) < 20)
        gnc_par.pontos_bordejar = tack_points([x,y], gnc_par.waypoints(waypointId), d_t, theta_t, alpha_tw);
    end
end

end

function waypoints_t=tack_points(p0, p1, d_t, alpha_t)
    global gnc_par

    gnc_par.isBordejando = true;
    
    x0 = p0(1,1);
    y0 = p0(2,1);
    x1 = p1(1,1);
    y1 = p1(2,1);           

    %finding line A
    a_A = (y1 - y0) / (x1 - x0);
    b_A = y0 - (a_A * x0);
    
    alpha_AB = atan2(y1-y0,x1-x0);
    
    %finding line B
    tan_alpha_t = tan(alpha_t);

    if(alpha_aw - alpha_AB > 0)
        a_B = (-a_A + tan_alpha_t) / (-tan_alpha_t * a_A - 1);     
    else
        a_B = (-a_A - tan_alpha_t) / (tan_alpha_t * a_A - 1);      
    end
    b_B = y0 - (a_B * x0);
    
    %first tacking point
    x_t = x0 + d_t;
    y_t = a_B*x_t + b_B;
    
    waypoints_t(:,1) = [x_t;y_t];
    i = 2;
    
    p_p = projecao2d(x_t, y_t, a_A, b_A);
    d_p0 = norm(p_p-p0);

    b_L1 = -a_A * x_t + y_t;

    if(b_L1 > b_A)
        b_L2 = b_A - (b_L1 - b_A);
    else
        b_L2 = b_A + (b_A - b_L1);
    end

    %number of tacking points
    n_t = floor(norm(p0-p1)/d_p0);

    delta_x = p_p(1) - x0;
    delta_y = p_p(2) - y0;

    p0_L1 = projecao2d(p_p(1,1), p_p(2,1), a_A, b_L1);
    p0_L2 = projecao2d(p_p(1,1), p_p(2,1), a_A, b_L2);

    for z = 1:n_t-1
        delta_x_tmp = z * delta_x;
        delta_y_tmp = z * delta_y;

        if mod(z,2) == 0
            p_tmp(1) = p0_L1(1,1) + delta_x_tmp;
            p_tmp(2) = p0_L1(2,1) + delta_y_tmp;
            waypoints_t(:,i) = p_tmp;
            i = i + 1;
        else
            aux = abs(alpha_tw - abs(alpha_AB));
            aux = rad2deg(aux);
            delta_xaux = aux * delta_x/31;
            delta_yaux = aux * delta_y/31;
            p_tmp(1) = p0_L2(1,1) + delta_x_tmp - delta_xaux;
            p_tmp(2) = p0_L2(2,1) + delta_y_tmp - delta_yaux;
            waypoints_t(:,i) = p_tmp;
            i = i + 1;
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

function tst=record_control
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
    tst = 0;
end

function tst=verify_movement
global gnc_par
    gnc_par.last_d_p1 = gnc_par.d_p1;
    gnc_par.d_p1 = norm(p-gnc_par.p1);

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