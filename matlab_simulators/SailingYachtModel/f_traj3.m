function desired_heading=f_traj3(V_in2)
global par

x = V_in2(1);
y = V_in2(2);
phi = V_in2(3);
par.psi = V_in2(4);
u = V_in2(5);
v = V_in2(6);
p = V_in2(7);
r = V_in2(8);

lastLocation = [x;y];
% desired_heading = 0;

[l, c] = size(par.waypoints);
if(c ~= 0)
    if (par.distanciaAlvo < 10)
        if (par.isBordejando)
            [l, c] = size(pontos_bordejar);
            if (par.waypointBId < c)
                par.waypointBId = par.waypointBId + 1;
                nextLocation = pontos_bordejar(:,waypointBId);
            else
                par.isBordejando = false;
                par.waypointBId = 1;
            end
        else
            [l,c] = size(par.waypoints);
            par.waypointId = par.waypointId + 1;
            if (mod(par.waypointId,c+1) == 0)
                par.waypointId = 1;
            end
            nextLocation = par.waypoints(:,par.waypointId);
        end
    else
        if (par.isBordejando)
            nextLocation = par.pontos_bordejar(:,par.waypointBId);
        else
            nextLocation = par.waypoints(:,par.waypointId);
        end
    end
    if(par.controle == 0)
        lastlastLocation = lastLocation;
        distanciaInicial = norm(lastLocation-nextLocation);
    end
    par.distanciaAlvo = norm(lastLocation-nextLocation);
end

biruta = par.alpha_w - par.psi;
deltaY = nextLocation(2,1) - lastLocation(2,1);
deltaX = nextLocation(1,1) - lastLocation(1,1);
desired_heading = atan2(deltaY,deltaX);

end