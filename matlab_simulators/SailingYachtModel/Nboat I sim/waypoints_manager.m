function w_duo=waypoints_manager(V_in)
global gnc_par

x = V_in(1);
y = V_in(2);
phi = V_in(3);
psi = V_in(4);
u = V_in(5);
v = V_in(6);
p = V_in(7);
r = V_in(8);


[l,c] = size(V_in);
index = 1;

for i = 9:2:l-1
    waypoints_vec(index,1) = V_in(i);
    waypoints_vec(index,2) = V_in(i+1);
    index = index + 1;
end

P = [x;y];

waypoints_size = 0;
[l, c] = size(waypoints_vec);

if l > c
    waypoints_size = l;
else
    waypoints_size = c;
end

dist = norm(P - waypoints_vec(gnc_par.waypointId_2,:)');

if dist < 5
    gnc_par.waypointId_1 = gnc_par.waypointId_1 + 1;
    gnc_par.waypointId_2 = gnc_par.waypointId_2 + 1;
    
    if mod(gnc_par.waypointId_1,waypoints_size+1) == 0
        gnc_par.waypointId_1 = 1;
        gnc_par.waypointId_2 = 2;
    end
    
    if mod(gnc_par.waypointId_2,waypoints_size+1) == 0
        gnc_par.waypointId_2 = 1;
    end
    
end

w_duo(:,1) = waypoints_vec(gnc_par.waypointId_1,:);
w_duo(:,2) = waypoints_vec(gnc_par.waypointId_2,:);

end