% interpreted Matlab function "f.m" for the Simulink file "sailboatModel.slx"
% This function describes the dynamics of a 4DOF sailing yacht model
% and gives the derivative of the state X and the sail angle delta_s.
% The input vector V_in contains the system state and the control input vector. 
%
% For the model description, notations, equations and parameters,
% see Xiao and Jouffroy, "Modeling and nonlinear heading control of sailing
% yachts", IEEE Journal of Oceanic Engineering, vol. 39, no. 2., pp. 256-268, 2014.
% 
% Jerome Jouffroy, Jiaxi He and Lin Xiao, 2014.
% University of Southern Denmark.



function X_dot_ext=sailboat_model(V_in)
 
% use the system parameters
global par

% retrieve the system state from the field input vector "V_in"
x = V_in(4);
y = V_in(5);
phi = V_in(6);
psi = V_in(7);
u = V_in(8);
v = V_in(9);
p = V_in(10);
r = V_in(11);
wind_angle = V_in(12);
vt = V_in(13);
water_angle =  V_in(14);
water_spd =  V_in(15);
nu = [ u ; v ; p ; r ];

% retrieve the input signals from the vector "V_in"
delta_r = V_in(1);
delta_sbar = V_in(2);
y_w = V_in(3);

% evaluate the matrix M and C in the model
M_RB = [ par.m   0      0           0 
         0      par.m   0           0 
         0       0    par.Ixx   -par.Ixz 
         0       0    -par.Ixz   par.Izz];
     
C_RB = [0       -par.m*r 0  0 
        par.m*r   0      0  0 
        0         0      0  0 
        0         0      0  0];

M_A = [par.a11   0          0         0
        0      par.a22   par.a24   par.a26
        0      par.a24   par.a44   par.a46
        0      par.a26   par.a46   par.a66];
    
C_A = [                 0                                0         0   -par.a22*nu(2)-par.a24*nu(3)-par.a26*nu(4)
                        0                                0         0    par.a11*nu(1) 
                        0                                0         0        0
       par.a22*nu(2)+par.a24*nu(3)+par.a26*nu(4)   -par.a11*nu(1)  0        0];

M = M_RB + M_A;
C = C_RB + C_A;

% calculate the tau vector, ie forces and moments generated from:
% the sail
v_t = [ vt*cos(wind_angle); vt*sin(wind_angle); 0 ];
v_tw = log(abs(par.z_s)*cos(phi)/par.h0)/log(par.h1/par.h0)*v_t;

R1 = [ cos(-psi) -sin(-psi) 0
       sin(-psi)  cos(-psi) 0
           0         0      1];
       
R2 = [ 1     0          0
       0  cos(-phi)  -sin(-phi)
       0  sin(-phi)  cos(-phi)];
   
v_tb = R2*R1*v_tw; % wind expressed in the body frame
V_in = [ u ; v ; 0 ];
V_awb = v_tb - V_in - cross([p;0;r],[par.xs;par.ys;par.zs]);
V_awu = V_awb(1);
V_awv = V_awb(2);
alpha_aw = atan2(V_awv,-V_awu);

% (sail luffing or not)
if alpha_aw>delta_sbar
    delta_s = delta_sbar;
elseif alpha_aw<-delta_sbar
    delta_s = -delta_sbar;
else
    delta_s = alpha_aw;
end

alpha_as = alpha_aw - delta_s;

[Cls,Cds] = sailcoef(alpha_as);
Ls = 0.5*par.rho_a*par.As*(V_awu^2+V_awv^2)*Cls;
Ds = 0.5*par.rho_a*par.As*(V_awu^2+V_awv^2)*Cds;

tau_sail = [Ls*sin(alpha_aw)-Ds*cos(alpha_aw); Ls*cos(alpha_aw)+Ds*sin(alpha_aw);-(Ls*cos(alpha_aw)+Ds*sin(alpha_aw))*par.zs; -(Ls*sin(alpha_aw)-Ds*cos(alpha_aw))*par.Xce*sin(delta_s)+(Ls*cos(alpha_aw)+Ds*sin(alpha_aw))*(par.Xm-par.Xce*cos(delta_s))];
Mzs = tau_sail(4);

% the rudder
v_aru = -u+r*par.yr;
v_arv = -v-r*par.xr + p*par.zr;
alpha_ar = atan2(v_arv,-v_aru);
alpha_a = alpha_ar-delta_r;
[Clr,Cdr] = ruddercoef(alpha_a);
Cdr = Cdr+Clr^2*par.Ar/(pi*2*par.zeta_r*par.d_r^2);

Lr = 0.5*par.rho_w*par.Ar*(v_aru^2+v_arv^2)*Clr;
Dr = 0.5*par.rho_w*par.Ar*(v_aru^2+v_arv^2)*Cdr;

tau_rudder = [Lr*sin(alpha_ar)-Dr*cos(alpha_ar); Lr*cos(alpha_ar)+Dr*sin(alpha_ar); -(Lr*cos(alpha_ar)+Dr*sin(alpha_ar))*par.zr; (Lr*cos(alpha_ar)+Dr*sin(alpha_ar))*par.xr];
Mzr = tau_rudder(4);

% the tau vector is finally given by:
tau = tau_sail + tau_rudder;

% calculate the damping forces and moments:
% from the keel
v_aku = -u + r*par.yk;
v_akv = -v - r*par.xk+p*par.zk;
alpha_ak = atan2(v_akv,-v_aku);
alpha_e = alpha_ak;
[Clk,Cdk] = keelcoef(alpha_e);
Cdk = Cdk + Clk^2*par.Ak/(pi*2*par.zeta_k*par.d_k^2);

Lk = 0.5*par.rho_w*par.Ak*(v_aku^2+v_akv^2)*Clk;
Dk = 0.5*par.rho_w*par.Ak*(v_aku^2+v_akv^2)*Cdk;

D_keel = [ -Lk*sin(alpha_ak)+Dk*cos(alpha_ak); -Lk*cos(alpha_ak)-Dk*sin(alpha_ak); -(-Lk*cos(alpha_ak)-Dk*sin(alpha_ak))*par.zk; -(Lk*cos(alpha_ak)+Dk*sin(alpha_ak))*par.xk];

% from the hull
v_ahu = -u + r*par.yh;
v_ahv = (-v-r*par.xh + p*par.zh)/cos(phi);
v_ah = sqrt(v_aku^2+v_akv^2);
alpha_ah = atan2(v_ahv,-v_ahu);
Frh = resistancehull(v_ah);

D_hull = [Frh*cos(alpha_ah);-Frh*sin(alpha_ah)*cos(phi); Frh*sin(alpha_ah)*cos(phi)*par.zh; -Frh*sin(alpha_ah)*cos(phi)*par.xh];

% from heel and yaw
% (compute first eta_dot and thereby phi_dot and psi_dot)
J = [cos(psi) -sin(psi)*cos(phi) 0 0; sin(psi) cos(psi)*cos(phi) 0 0; 0 0 1 0; 0 0 0 cos(phi)];
eta_dot = J*nu;
phi_dot = eta_dot(3);
psi_dot = eta_dot(4);

D_heelandyaw = [0;0;par.c*phi_dot*abs(phi_dot);par.d*psi_dot*abs(psi_dot)*cos(phi)]; 

% compute total damping vector D
D = D_keel + D_hull + D_heelandyaw;

% righting moment plus internal moving mass system (ie transversal weight)
phi_deg = phi*180/pi;
M_xw = -y_w*par.w_c*par.y_bm*cos(phi);
M_zw = -y_w*par.w_c*par.x_c*sin(abs(phi));
G = [ 0 ; 0 ; par.a*phi_deg^2+par.b*phi_deg + M_xw ; M_zw];

% computation of nu_dot
nu_dot = -M\(C*nu) - M\D - M\G + M\tau; 
 
% output the derivative of the state extended with the sail angle
X_dot_ext = [ eta_dot   ; 
              nu_dot   ;
              delta_s];


%------------------------------------------------------------------------------------------------------------------------------
function [Cls,Cds] = sailcoef(attack)
% generate a lookup table for the lift/drag coefficients for the sail
% and compute Cls/Cds from the lookup table using interpolation.

% lookup table
xdata = linspace(-pi,pi,73); % every 5 degrees
xdata = xdata/pi*180;

% lift curve
yldata = [fliplr([0 0.15 0.32 ...
    0.48 0.7 0.94 1.15 1.3 1.28 1.15 1.1 1.05 1 0.9 0.82 0.72 0.68 0.56 0.48 0.32 0.21 0.08 ...
    -0.06 -0.18 -0.3 -0.4 -0.53 -0.64 -0.72 -0.84 -0.95 -1.04 -1.1 -1.14 -1.08 -0.76 0])*(-1) ...
    [0.15 0.32 ...
    0.48 0.7 0.94 1.15 1.3 1.28 1.15 1.1 1.05 1 0.9 0.82 0.72 0.68 0.56 0.48 0.32 0.21 0.08 ...
    -0.06 -0.18 -0.3 -0.4 -0.53 -0.64 -0.72 -0.84 -0.95 -1.04 -1.1 -1.14 -1.08 -0.76 0]];

% drag curve
yddata = [fliplr([0.1 0.12 0.14 ...
    0.16 0.19 0.26 0.35 0.46 0.54 0.62 0.7 0.78 0.9 0.98 1.04 1.08 1.16 1.2 1.24 1.26 ...
    1.28 1.34 1.36 1.37 1.33 1.31 1.28 1.26 1.25 1.2 1.1 1.04 0.88 0.8 0.64 0.38 0.1])...
    [0.12 0.14 ...
    0.16 0.19 0.26 0.35 0.46 0.54 0.62 0.7 0.78 0.9 0.98 1.04 1.08 1.16 1.2 1.24 1.26 ...
    1.28 1.34 1.36 1.37 1.33 1.31 1.28 1.26 1.25 1.2 1.1 1.04 0.88 0.8 0.64 0.38 0.1]];

% fit the input angle of attack into the interval [-pi,pi]
if attack > pi
    attack = mod(attack+pi,2*pi) - pi;
else
    if attack < -pi
        attack = mod(attack-pi,-2*pi) + pi;
    end
end

% interpolation
attack = attack/pi*180;
Cls = interp1(xdata,yldata,attack,'pchip');
Cds = interp1(xdata,yddata,attack,'pchip');


%------------------------------------------------------------------------------------------------------------------------------
function [Clr,Cdr] = ruddercoef(attack)
% generate a lookup table for the lift/drag coefficients for the sail
% and compute Cls/Cds from the lookup table using interpolation.

% lookup table
xdata = linspace(-pi,pi,73); % every 5 degrees
xdata = xdata/pi*180;

% lift curve
yl = fliplr([0 0.42 0.73 ...
    0.95 1.1 1.165 1.18 1.155 1.12 1.065 1 0.92 0.83 0.72 0.62 0.48 0.33 0.16])*(-1);
yldata = [fliplr([0 0.42 0.73 ...
    0.95 1.1 1.165 1.18 1.155 1.12 1.065 1 0.92 0.83 0.72 0.62 0.48 0.33 0.16 0 yl])*(-1) ...
    [0.42 0.73 ...
    0.95 1.1 1.165 1.18 1.155 1.12 1.065 1 0.92 0.83 0.72 0.62 0.48 0.33 0.16 0 yl]];

% drag curve
yd = fliplr([0 0.03 0.06 ...
    0.1 0.17 0.3 0.48 0.74 0.98 1.18 1.34 1.5 1.65 1.76 1.89 1.97 2.01 2.05]);
yddata = [fliplr([0 0.03 0.06 ...
    0.1 0.17 0.3 0.48 0.74 0.98 1.18 1.34 1.5 1.65 1.76 1.89 1.97 2.01 2.05 2.08 yd])...
    [0.03 0.06 ...
    0.1 0.17 0.3 0.48 0.74 0.98 1.18 1.34 1.5 1.65 1.76 1.89 1.97 2.01 2.05 2.08 yd]];

% fit the input angle of attack into the interval [-pi,pi]
if attack > pi
    attack = mod(attack+pi,2*pi) - pi;
else
    if attack < -pi
        attack = mod(attack-pi,-2*pi) + pi;
    end
end

% interpolation
attack = attack/pi*180;
Clr = interp1(xdata,yldata,attack,'pchip');
Cdr = interp1(xdata,yddata,attack,'pchip');


%------------------------------------------------------------------------------------------------------------------------------
function [Clk,Cdk] = keelcoef(attack)
% generate a lookup table for the lift/drag coefficients for the sail
% and compute Cls/Cds from the lookup table using interpolation.

% lookup table
xdata = linspace(-pi,pi,73); % every 5 degrees
xdata = xdata/pi*180;

% lift curve
yl = fliplr([0 0.425 0.74 ...
    0.94 1.1 1.17 1.19 1.16 1.12 1.07 0.99 0.92 0.84 0.74 0.63 0.49 0.345 0.185])*(-1);
yldata = [fliplr([0 0.425 0.74 ...
    0.94 1.1 1.17 1.19 1.16 1.12 1.07 0.99 0.92 0.84 0.74 0.63 0.49 0.345 0.185 0 yl])*(-1) ...
    [0.425 0.74 ...
    0.94 1.1 1.17 1.19 1.16 1.12 1.07 0.99 0.92 0.84 0.74 0.63 0.49 0.345 0.185 0 yl]];

% drag curve
yd = fliplr([0 0.04 0.07 ...
    0.1 0.17 0.3 0.49 0.76 0.98 1.19 1.34 1.5 1.65 1.77 1.88 1.96 2.01 2.05]);
yddata = [fliplr([0 0.04 0.07 ...
    0.1 0.17 0.3 0.49 0.76 0.98 1.19 1.34 1.5 1.65 1.77 1.88 1.96 2.01 2.05 2.09 yd])...
    [0.04 0.07 ...
    0.1 0.17 0.3 0.49 0.76 0.98 1.19 1.34 1.5 1.65 1.77 1.88 1.96 2.01 2.05 2.09 yd]];

% fit the input angle of attack into the interval [-pi,pi]
if attack > pi
    attack = mod(attack+pi,2*pi) - pi;
else
    if attack < -pi
        attack = mod(attack-pi,-2*pi) + pi;
    end
end

% interpolation
attack = attack/pi*180;
Clk = interp1(xdata,yldata,attack,'pchip');
Cdk = interp1(xdata,yddata,attack,'pchip');


%------------------------------------------------------------------------------------------------------------------------------
function F = resistancehull(alpha_a)

xdata = linspace(0,6,13); % every 0.5m/s
ydata = [0 0.15 0.35 0.5 0.675 0.825 1.175 1.4 2 4.85 9.85 18.46 27.5]*1000;

% interpolation
if alpha_a <= 6
    F = interp1(xdata,ydata,alpha_a,'pchip');
else
    F = interp1(xdata,ydata,alpha_a,'pchip','extrap');
end