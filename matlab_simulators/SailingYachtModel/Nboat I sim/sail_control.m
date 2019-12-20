function delta_s = sail_control(V_in)
global gnc_par
    psi = V_in(1);
    gamma_tw = V_in(2);
    wind_spd = V_in(3);
    water_angle =  V_in(4);
    water_spd =  V_in(5);
    
    gamma_tw_deg = rad2deg(gamma_tw);
    psi_deg = rad2deg(psi);
    
    gamma_tw = gamma_tw - pi;
    gamma_tw = constrain(gamma_tw);
    
    %wind direction measured by a windvane
    gamma_aw = gamma_tw + psi;
    gamma_aw = constrain(gamma_aw);
    
    gnc_par.gamma_aw = gamma_aw;
    gnc_par.gamma_aw_vec(gnc_par.gamma_aw_vec_count, 1) = rad2deg(gamma_aw);
    gnc_par.gamma_aw_vec_count = gnc_par.gamma_aw_vec_count + 1;
    gnc_par.gamma_tw = gamma_tw;
    
    %desired sail position |-180 < gamma_aw < 180|
    delta_s = abs(gamma_aw)/2;
end