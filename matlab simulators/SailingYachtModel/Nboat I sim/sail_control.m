function delta_s = sail_control(V_in)
    psi = V_in(1);
    alpha_vr = V_in(2);
    wind_spd = V_in(3);
    water_angle =  V_in(4);
    water_spd =  V_in(5);
    
    if alpha_vr > pi
        alpha_vr = alpha_vr - 2*pi;
    end
    if alpha_vr < -pi
        alpha_vr = alpha_vr + 2*pi;
    end
    
    %wind direction in BODY frame
    alpha_va = alpha_vr + psi;
    
    %desired sail position
    delta_s = abs(alpha_va)/2;
end

