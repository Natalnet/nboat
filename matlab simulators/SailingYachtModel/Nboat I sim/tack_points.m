function waypoints_t=tack_points(p0, p1, d_t, theta_t, alpha_tw)
    global gnc_par
    global mdl_par

    gnc_par.isBordejando = true;
    alpha_aw = mdl_par.alpha_aw;
    
    x0 = p0(1,1);
    y0 = p0(2,1);
    x1 = p1(1,1);
    y1 = p1(2,1);           

    %finding line A
    if (x1 - x0) == 0
        a_A = 10000000000000;
    else
        a_A = (y1 - y0) / (x1 - x0);
    end
    
    b_A = y0 - (a_A * x0);
    
    alpha_p = atan2(y1-y0,x1-x0);
    
    %finding line B
    tan_theta_t = tand(theta_t);

    if(alpha_aw - alpha_p > 0)
        a_B = (-a_A + tan_theta_t) / (-tan_theta_t * a_A - 1);     
    else
        a_B = (-a_A - tan_theta_t) / (tan_theta_t * a_A - 1);      
    end
    b_B = y0 - (a_B * x0);
    
    %first tacking point
    H = d_t/sind(theta_t);
    
    a = 1 + a_B^2;
    b = -2*x0+2*a_B*b_B-2*a_B*y0;
    c = x0^2 + y0^2 + b_B^2 -2*y0*b_B - H^2;
    
    delta = b^2 - 4*a*c;
    
    x_t1 = (-b + sqrt(delta))/(2*a);
    y_t1 = a_B*x_t1 + b_B;
    
    x_t2 = (-b - sqrt(delta))/(2*a);
    y_t2 = a_B*x_t2 + b_B;
    
    d_t1_p1 = norm([x_t1;y_t1]-p1);
    d_t2_p1 = norm([x_t2;y_t2]-p1);
    
    if min(d_t1_p1,d_t2_p1) == d_t1_p1
        x_t = x_t1;
        y_t = y_t1;
    else
        x_t = x_t2;
        y_t = y_t2;
    end
    
    waypoints_t(1,:) = [x_t;y_t];
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
            waypoints_t(i,:) = p_tmp;
            i = i + 1;
        else
            aux = abs(alpha_tw - abs(alpha_p));
            aux = rad2deg(aux);
            delta_xaux = aux * delta_x/31;
            delta_yaux = aux * delta_y/31;
            p_tmp(1) = p0_L2(1,1) + delta_x_tmp - delta_xaux;
            p_tmp(2) = p0_L2(2,1) + delta_y_tmp - delta_yaux;
            p_tmp(1) = p0_L2(1,1) + delta_x_tmp;
            p_tmp(2) = p0_L2(2,1) + delta_y_tmp;
            waypoints_t(i,:) = p_tmp;
            i = i + 1;
        end
    end
    close all
    plot(waypoints_t(:,1),waypoints_t(:,2));
    j = [min(p1(1),p0(1)):1:max(p1(1),p0(1))];
    hold on
    plot(j,a_A*j+b_A);
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