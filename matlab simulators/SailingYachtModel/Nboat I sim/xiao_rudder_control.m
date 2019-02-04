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
    
    tw(1) = V_in(10);           %vento real (angulo, modulo)
    tw(2) = V_in(11);
    tc(1) = V_in(12);           %corrente real (angulo, modulo)
    tc(2) = V_in(13);
    
    delta_s = V_in(14);
    
    
    V_twu = tw(2)*cos(tw(1));   %velocidade do vento real em x
    V_twv = tw(2)*sin(tw(1));   %velocidade do vento real em y 
    V_tw = [V_twu; V_twv];      %vetor do vento real
    
    V_tcu = tc(2)*cos(tc(1));   %velocidade da corrente real em x
    V_tcv = tc(2)*sin(tc(1));   %velocidade da corrente real em y
    V_tc = [V_tcu; V_tcv];      %vetor da corrente real
    
    U = [u; v];
    
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
    
    %Gains
    K1 = 1;
    Kyaw = -2*(Izz - Nr);
    Kls = 2;
    Kd0 = 0.1;
    Kds = 1.5;
    Klr = 4.5;
    
    %Variables
    V_aw = V_tw - U;                            %velocidade do vento aparente
    mod_V_aw = sqrt(V_aw(1)^2 + V_aw(2)^2);
    alpha_aw = atan2(V_aw(2),-V_aw(1));         %atan2(vaw,-uaw)
    alpha_s = alpha_aw - delta_s;               %ângulo de atk da vela
    
    V_ach = V_tc - U;                           %velocidade da corrente aparente no leme
    V_acru = -V_ach(1) + r*y_r;
    V_acrv = -V_ach(2) - r*x_r + p*z_r;
    V_acr = sqrt(V_acru^2 + V_acrv^2);
    alpha_acr = atan2(V_acrv, -V_acru);         %angulo da corrente aparente
    
    
    A = -(1+K1*cos(phi))*r - (K1+cos(phi))*(psi-psi_d);
    B = (Izz - Nr) - (-Xu + Yv)*u*v + (Kyaw*r*abs(r)*(cos(phi)^3)) - (0.5*rho_a*As*(mod_V_aw^2));
    C1 = Kls*sin(alpha_s)*cos(alpha_aw) + (Kd0 + Kds*sin(alpha_s)^2)*sin(alpha_aw);
    C2 = (x_m - x_mce*cos(delta_s)) - (Kls*sin(alpha_s)*sin(alpha_aw)-(Kd0 + Kds*sin(alpha_s)^2)*cos(alpha_aw));
    C3 = x_mce*sin(delta_s);
    C = C1 + C2 + C3;
    D = -Klr*(abs(x_r)/2)*rho_w*Ar*V_acr^2;
    
    alpha_r = A*B*C/D;
    if alpha_r > 1
        alpha_r = 1;
    end
    if alpha_r < -1
        alpha_r = -1;
    end
    
    delta_r = alpha_acr - asin(alpha_r);
end