%SIMULAR BORDEJO
% mudar o valor das condições iniciais

clc;
clear;

global par

incAng = 60/20;
incDist = 0.9/20;

contPar = 1;
contIt = 1;

ini_ang = -150;

array_tempo = zeros(7, 961);
array_dist = zeros(7, 961);
array_ang = zeros(7, 961);

% array_tempo = zeros(1, 36);
% array_dist = zeros(1, 36);
% array_ang = zeros(1, 36);

ang = 20;
dist = 0.1;
var_print = 0;

tic;

while contIt <= 1
    for i = 0.1:0.8/30:0.9
        for j = 20:60/30:80
            set_param('SailingYachtModel/controleTraj/distBord', 'Value' , num2str(i));
            set_param('SailingYachtModel/controleTraj/angBord', 'Value' , num2str(j));
            set_param('SailingYachtModel/4DOF nonlinear sailing yacht model/vento', 'Value', num2str(deg2rad(ini_ang)));
            sim('SailingYachtModel');

            if par.flag == 1
                % o que vai acontec er quando os parâmetros não fazem o veleiro
                % chegar ao alvo
                [l, c] = size(X.time);
                array_tempo(contIt, contPar) = 0;
                array_dist(contIt, contPar) = i;
                array_ang(contIt, contPar) = j;
                contPar = contPar + 1;            
                par.flag = 0;
            else
                [l, c] = size(X.time);
                array_tempo(contIt, contPar) = X.time(l,1);
                array_dist(contIt, contPar) = i;
                array_ang(contIt, contPar) = j;
                var_print = array_tempo(contIt, contPar);
                contPar = contPar + 1;
            end
            
            if contPar ~= 961
                contPar = mod(contPar, 961);
            end
            fprintf('ContPar = %d; tempo = %3.2f', contPar, var_print);
            %plot_sim;
        end
    end
    
    ini_ang = ini_ang - 10;
    
    if ini_ang == -180
        ini_ang = 180;
    end
    contIt = contIt + 1;
end
t1 = toc;

% set_param('SailingYachtModel/IC', 'Value' ,'[0; 0; 0; 0; 0; 0]')
% set_param('SailingYachtModel', 'SimulationCommand' ,'pause')