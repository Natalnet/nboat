function psi_d = LOS_path_follow(V_in)
    global gnc_par
    
    x = V_in(1);
    y = V_in(2);
    phi = V_in(3);
    psi = V_in(4);
    u = V_in(5);
    v = V_in(6);
    p = V_in(7);
    r = V_in(8);
    
    %waypoints k and k+1
    x1 = V_in(9);
    y1 = V_in(10);
    x2 = V_in(11);
    y2 = V_in(12);
    
    alpha_tw = V_in(13);
    gamma_tw = alpha_tw;
    
    r = gnc_par.R;
    %K_ct = gnc_par.K_ct;
    
    U = sqrt(u^2 + v^2);
    
    if U == 0
        beta = 0;
    else
       beta = asin(v/U); 
    end
    
    % (x_los, y_los) pela equação achada na net
    %d_x = x2 - x1;
    %d_y = y2 - y1;
    %d_r = sqrt(d_x^2 + d_y^2);
    %D = x1*y2 - x2*y1;    
    %x_los = D*d_y + sign(d_y)*d_x*sqrt(r^2*d_r^2 - D^2);
    %y_los = -D*d_x+abs(d_y)*sqrt(r^2*d_r^2 - D^2);
    
    % (x_los, y_los) por Fossen
    d_x = x2 - x1;
    d_y = y2 - y1;
    d = d_y/d_x;
    g = y1 - d*x1;
    a = 1 + d^2;
    b = 2*(d*g - d*y - x);
    c = x^2 + y^2 + g^2 - 2*g*y - r^2;
    
    if abs(d_x) > 0
        if d_x > 0
            x_los = (-b + sqrt(b^2 - 4*a*c))/2*a;
        end
        if d_x < 0
            x_los = (-b - sqrt(b^2 - 4*a*c))/2*a;
        end
        y_los = d*(x_los - x1) + y1;
    end
    if d_x == 0
        x_los = x1;
        if d_y > 0
            y_los = real(y + sqrt(r^2 - (x_los - x)^2)); 
        end
        if d_y < 0
            y_los = real(y - sqrt(r^2 - (x_los - x)^2));
        end
    end
    
    alpha_k = atan2(d_y,d_x);    
    chi_p = alpha_k;
    
    %enclosure-based steering
%     chi_d = atan2(y_los - y, x_los - x);
%     psi_d = chi_d - beta;


    gamma_tw = gamma_tw - pi;
    gamma_tw = constrain(gamma_tw);
    
    %angulo de ataque do vento atual
    alpha = psi - gamma_tw;
    alpha = constrain(alpha);
    % gnc_par.alpha(gnc_par.Vd_count) = alpha;

    %angulo de ataque do vento com o veleiro quando seguindo a direção alvo
    alpha_d = alpha_k - gamma_tw;
    alpha_d = constrain(alpha_d);
   
    
    %lookahead-based steering    
    e = -(x - x1)*sin(alpha_k) + (y - y1)*cos(alpha_k);
    delta = sqrt(r^2 - e^2);
    K_ct = 1/delta;
    chi_r = atan(-K_ct*e);
    gnc_par.e(gnc_par.conte, 1) = e;
    gnc_par.conte = gnc_par.conte + 1;
    
    chi_d = chi_p + chi_r;
    
    psi_d = chi_d - beta;
    
%     if psi_d > 0
%         psi_d = psi_d - 2*pi;
%     elseif psi_d < 0
        psi_d = psi_d + 2*pi;
% %     end
%     
%     if psi_d > 2*pi
%         psi_d = psi_d - 2*pi;
%     elseif psi_d < -2*pi
%         psi_d = psi_d + 2*pi;
%     end
    
%     if alpha < alpha_d
%         psi_d = psi_d - pi;
%     else
%         
%     end
        

%psi_d = alpha_k;
end