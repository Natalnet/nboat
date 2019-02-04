%Entrada: V_in = 0-8 estado
%                9 orientação desejada
%                10-13perturbações
%                14 posição da vela,

function delta_r = xiao_rudder_control(V_in)
    global mdl_par
    x = V_in(1);
    y = V_in(2);
    phi = V_in(3);
    psi = V_in(4);
    u = V_in(5);
    v = V_in(6);
    p = V_in(7);
    r = V_in(8);
    
    psi_d = V_in(9);
    
    %Constants
    Izz = mdl_par.Izz;
    Nr = mdl_par.a66;
    Xu = mdl_par.a11;
    Yv = mdl_par.a22;
    rho_a = mdl_par.rho_a;
    As = mdl_par.As;
    rho_w = mdl_par.rho_w;
    Ar = mdl_par.Ar;
    x_m = mdl_par.Xm;           %posição x do mastro no referencial do barco
    x_mce = mdl_par.Xce;        %distância entre o mastro e o centro de esforço
    x_r = mdl_par.xr;
    y_r = mdl_par.yr;
    z_r = mdl_par.zr;
    V_aw = mdl_par.V_aw;
    alpha_s = mdl_par.alpha_s;
    delta_s = mdl_par.delta_s;
    alpha_aw = mdl_par.alpha_aw;
    V_ar = mdl_par.V_ar;
    alpha_ar = mdl_par.alpha_ar;
    
    %Gains
    K1 = 1;
    Kyaw = -2*(Izz - Nr);
    %Kyaw = 0;
    Kls = 2;
    Kd0 = 0.1;
    Kds = 1.5;
    Klr = 50;    
    
    A = -(1+K1*cos(phi))*r - (K1+cos(phi))*(psi-psi_d);
    B = (Izz - Nr) - (-Xu + Yv)*u*v + (Kyaw*r*abs(r)*(cos(phi)^3)) - (0.5*rho_a*As*(V_aw^2));
    C1 = Kls*sin(alpha_s)*cos(alpha_aw) + (Kd0 + Kds*sin(alpha_s)^2)*sin(alpha_aw);
    C2 = (x_m - x_mce*cos(delta_s)) - (Kls*sin(alpha_s)*sin(alpha_aw)-(Kd0 + Kds*sin(alpha_s)^2)*cos(alpha_aw));
    C3 = x_mce*sin(delta_s);
    C = C1 + C2 + C3;
    D = -Klr*(abs(x_r)/2)*rho_w*Ar*V_ar^2;
    
    alpha_r = A*B*C/D;
    
    if alpha_r > 1
        alpha_r = 1;
    end
    if alpha_r < -1
        alpha_r = -1;
    end
    
    delta_r = alpha_ar - asin(alpha_r);
end