%entrada: direção do vento quando o veleiro estiver apontando para o
%destino
%funcionamento: verifica se o ângulo para o próximo destino é navegável.
%se não for, mantem o veleiro em um ângulo navegável e fica verificando o
%ângulo até o destino;
%saída: theta_t graus em relação ao vento7
%ideia: deve manter um certo ângulo com o vento

function psi_d=need_tack(V_in)
global gnc_par

x = V_in(1);
y = V_in(2);
phi = V_in(3);
psi = V_in(4);
u = V_in(5);
v = V_in(6);
p = V_in(7);
r = V_in(8);

psi_d = V_in(9);
psi_t = V_in(10);
gamma_tw = V_in(11);

%alpha_tw -> vento indo para

%angulo de ataque do vento no casco quando estiver apontando para o destino
alpha = psi_d - gnc_par.gamma_tw;

alpha = constrain(alpha);

%verifica se o desired_heading é navegável
%se não for muda o desired_heading para psi_t do vento
if gnc_par.tack == 0
    if(alpha < deg2rad(40) && alpha >= 0)
        psi_d = psi_d + psi_t;
        gnc_par.tack = 1;
    elseif(alpha > deg2rad(-40) && alpha <= 0)
        psi_d = psi_d - psi_t;
        gnc_par.tack = 1;
    end
else
    if e > 10
        psi_d = psi_d;
    end
end
end