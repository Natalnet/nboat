function delta_r = rudder_pid_heading(V_in)    
    heading_error = V_in(1); %heading error = sp - psi
    Kp = V_in(2);
    Ki = V_in(3);
    T = 0.1;

    if (heading_error > pi)
        heading_error = heading_error - 2*pi;
    else
        if (heading_error < -pi)
            heading_error = heading_error + 2*pi;
        end
    end
    
    delta_r = P(heading_error,Kp) + I(heading_error,Ki,T);
end

function out=P(current_error, gain)
  out = current_error*gain;
end

function out=I(current_error, gain, T)
    global par
    if (par.integrator > 0 && current_error < 0) || (par.Ianterior < 0 && current_error > 0)
        par.integrator = par.integrator + gain * current_error * 100 * T;
    else
        par.integrator = par.integrator + gain * current_error * T;
    end
    out = par.integrator;
end