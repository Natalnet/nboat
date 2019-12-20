function delta_r = rudder_pid_heading(V_in)    
    heading_error = V_in(1); %heading error = sp - psi
    Kp = V_in(2);
    Ki = V_in(3);

    if (heading_error > pi)
        heading_error = heading_error - 2*pi;
    else
        if (heading_error < -pi)
            heading_error = heading_error + 2*pi;
        end
    end
    
    delta_r = P(heading_error,Kp) + I(heading_error,Ki);
end

function out=P(current_error, gain)
  out = current_error*gain;
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