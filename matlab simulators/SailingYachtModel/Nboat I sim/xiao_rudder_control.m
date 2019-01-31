function delta_r = rudder_pid_heading(V_in)  
    global mdl_par
    heading_error = V_in(1); %heading error = sp - psi
    Kp = V_in(2);
    Ki = V_in(3);
    
    A = -(1+k1*cos(phi))*r - (k1+cos(phi))*(psi-psi_d);
    B = (Izz - Nr) - (-Xu + Yv)*u*v + (Kyaw*r*abs(r)*cos(phi).^3) - (0.5*rho_a*As*vaw^2);
    C1 = Kls*sin(alpha_s)*cos(alpha_aw) + (Kd0 + Kds*sin(alpha_s).^2)*sin(alpha_aw);
    C2 = (xm - xsm*cos(delta_s)) - (Kls*sin(alpha_s)*sin(alpha_aw)-(Kd0 + Kds*sin(alpha_s)^2)*cos(alpha_aw));
    C3 = xsm*sin(delta_s);
    C = C1 + C2 + C3;
    
    
    D = -Klr*(abs(xr)/2)*rho_w*Ar*var^2;
    
    delta_r = alpha_ar - asin(A*B*C/D);
    
    

end

function out=I(current_error, gain)
    global gnc_par
    gnc_par.T = get_param('sailboatModel','SimulationTime') - gnc_par.T;
    if (gnc_par.integrator > 0 && current_error < 0) || (gnc_par.integrator < 0 && current_error > 0)
        gnc_par.integrator = gnc_par.integrator + gain * current_error * 100 * gnc_par.T;
    else
        gnc_par.integrator = gnc_par.integrator + gain * current_error * gnc_par.T;
    end
    gnc_par.T = get_param('sailboatModel','SimulationTime');
    out = gnc_par.integrator;
end