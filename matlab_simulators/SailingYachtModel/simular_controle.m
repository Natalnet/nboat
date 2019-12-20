%SIMULAR BORDEJO
% mudar o valor das condições iniciais

clc;
clear;

global par

ini_ang = 0;
ini_ang_vento = 45;

contIt = 1;
contIt1 = 1;
contPar = 1;

array_controle = zeros(32, 400);
array_kp = zeros(32, 400);
array_ki = zeros(32, 400);
tempo_acomod2 = zeros(32, 400);
tempo_sub = zeros(32,400);
overshoot = zeros(32,400);
tempo_pico = zeros(32,400);
array_distance = zeros(32,400);
ini_ang_vec = zeros(8);

% array_tempo = zeros(1, 36);
% array_dist = zeros(1, 36);
% array_ang = zeros(1, 36);

tic;
    set_param('SailingYachtModel/4DOF nonlinear sailing yacht model/vento', 'Value', num2str(deg2rad(0)));
    angstring = strcat('[0;0;0;',num2str(deg2rad(ini_ang)), ';3;0;0;0]');
    set_param('SailingYachtModel/IC', 'Value' , angstring);
    while contIt <= 8
        for i = 1:0.5:10.5
            for j = 1:20
                set_param('SailingYachtModel/simple P heading controller/Kp', 'Value' , num2str(i));
                set_param('SailingYachtModel/simple P heading controller/Ki', 'Value' , num2str(j));
    %             set_param('SailingYachtModel/4DOF nonlinear sailing yacht model/vento', 'Value', num2str(deg2rad(ini_ang)));
                sim('SailingYachtModel');       
                teste = par.tempoDeAcomod2; 

                if par.flag == 1
                    % o que vai acontecer quando os parâmetros não fazem o veleiro
                    % chegar ao alvo
                    [l, c] = size(X.time);
                    array_controle(contIt, contPar) = 0;
                    array_kp(contIt, contPar) = i;
                    array_ki(contIt, contPar) = j;
                    contPar = contPar + 1;            
                    par.flag = 0;
                else
                    [l, c] = size(X.time);
                    array_controle(contIt, contPar) = X.time(l,1);
                    array_kp(contIt, contPar) = i;
                    array_ki(contIt, contPar) = j;
                    contPar = contPar + 1;               
                    tempo_acomod2(contIt, contPar) = par.tempoDeAcomod2;
                    tempo_sub(contIt, contPar) = par.temposub;
                    overshoot(contIt, contPar) = par.overshoot;
                    tempo_pico(contIt, contPar) = par.tempopico;
                    [ldist, cdist] = size(X.signals.values);
                    p0dist = [0 0];
                    pfdist = par.nextLocation;                
                    a_reta = (pfdist(2) - p0dist(2))/(pfdist(1) - p0dist(1));
                    b_reta = p0dist(2) - (a_reta * p0dist(1));
                    maior_dist = 0;
                    for idist = 1:ldist
                        p_reta = projecao2d(X.signals.values(idist, 1), X.signals.values(idist, 2), a_reta, b_reta);
                        dist_aux = norm(X.signals.values(idist,1:2)-p_reta');
                        if(dist_aux > maior_dist)
                            maior_dist = dist_aux;
                        end
                    end
                    array_distance(contIt, contPar) = maior_dist;                
                end

                if contPar ~= 400
                    contPar = mod(contPar, 400);
                end

                %plot_sim;
            end
        end

        ini_ang = ini_ang - 45;

        if ini_ang == -180
            ini_ang = 180;
        end

        angstring = strcat('[0;0;0;',num2str(deg2rad(ini_ang)), ';3;0;0;0]');

        set_param('SailingYachtModel/IC', 'Value' , angstring);
        
        ini_ang_vec(contIt) = ini_ang;

        contIt = contIt + 1;
    end
t1 = toc;

% set_param('SailingYachtModel/IC', 'Value' ,'[0; 0; 0; 0; 0; 0]')
% set_param('SailingYachtModel', 'SimulationCommand' ,'pause')