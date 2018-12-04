function delta_s = sail_control(V_in, wind)
    %get curent heading
    psi = V_in(4);
    
    %wind direction in world frame
    heeling = atan2(wind(2),wind(1)) - pi/2;
    
    
    if heeling > pi
        heeling = heeling - 2*pi;
    end
    if heeling < -pi
        heeling = heeling + 2*pi;
    end
    
    %wind direction in b frame
    biruta = heeling - psi;

    if(biruta < 0)
        biruta_s = -biruta;
    else
        biruta_s = biruta;
    end
    
    %desired sail position
    delta_s = biruta_s/2;
end

