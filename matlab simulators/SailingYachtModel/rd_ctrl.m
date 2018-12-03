function delta_r = rd_ctrl(V_in)
global par
erro_atual = V_in(1);
Kp = V_in(2);
Ki = V_in(3);
tempo_do_ciclo = 0.1;
rudder_min = -60;
rudder_medio = 0;
rudder_max = 60;

if (erro_atual > pi)
    erro_atual = erro_atual - 2*pi;
else if (erro_atual < -pi)
        erro_atual = erro_atual + 2*pi;
    end
end

angulo_rudder = 90 * (rad2deg(erro_atual)/180);

angulo_rudder = angulo_rudder * Kp;

if (par.Ianterior > 0 && erro_atual < 0) || (par.Ianterior < 0 && erro_atual > 0)
    par.Ianterior = par.Ianterior + Ki * erro_atual * 100 * tempo_do_ciclo;
else
    par.Ianterior = par.Ianterior + Ki * erro_atual * tempo_do_ciclo;
end

angulo_rudder = angulo_rudder + par.Ianterior;

if angulo_rudder > 90
    angulo_rudder = 90;
end
if angulo_rudder < -90
    angulo_rudder = -90;
end

if(erro_atual < 0)
    delta_r = rudder_min + (rudder_medio - rudder_min) * ((angulo_rudder + 90)/90);
else
    delta_r = rudder_medio + (rudder_max - rudder_medio) * (angulo_rudder/90);
end
delta_r = deg2rad(delta_r);
end

