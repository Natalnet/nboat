function V_out=ise(V_in)
global gnc_par

%boat state
x = V_in(1);
y = V_in(2);
phi = V_in(3);
psi = V_in(4);
u = V_in(5);
v = V_in(6);
p = V_in(7);
r = V_in(8);

%waypoints k and k+1
x1 = V_in(9);
y1 = V_in(10);
x2 = V_in(11);
y2 = V_in(12);

U = sqrt(u^2 + v^2);

if U == 0
    beta = 0;
else
   beta = asin(v/U); 
end

d_x = x2 - x1;
d_y = y2 - y1;

alpha_k = atan2(d_y,d_x);

course = psi + beta;
gnc_par.Vd(gnc_par.Vd_count, 1) = U*cos(alpha_k - course);
gnc_par.Vd_count = gnc_par.Vd_count + 1;

V_out = gnc_par.Vd(gnc_par.Vd_count-1, 1);

end