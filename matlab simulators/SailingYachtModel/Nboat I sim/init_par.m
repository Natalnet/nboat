% GUIDANCE PARAMETERS
global gnc_par
gnc_par.overshoot = 0;
gnc_par.tempopico = 0;
gnc_par.temposub = 0;
gnc_par.flagtemposub = true;
gnc_par.flagAcomod = false;
gnc_par.tempoDeAcomod = 0;
gnc_par.spvec = 0;
gnc_par.spveccont = 1;

gnc_par.dist_lateral = 0;
gnc_par.contador_teste = 1;
gnc_par.lastd_p1 = 0;
gnc_par.flag = 0;
gnc_par.contador_bug = 0;
gnc_par.psi = 0;
gnc_par.velocidade = 0;
gnc_par.contVel = 1;
gnc_par.integrator = 0;
gnc_par.d_p1 = 999999999;
gnc_par.waypoints = [];
gnc_par.waypointId = 1;
gnc_par.waypointId1 = 1;
gnc_par.nextLocation = [0;0];
gnc_par.waypointBId = 1;
gnc_par.isBordejando = false;
gnc_par.i = 1;
gnc_par.pontos_bordejar = eye(2,1);
gnc_par.controle = 0;
gnc_par.lastlastLocation = eye(2,1);
gnc_par.taxa_dist = 0.3;
gnc_par.angulo_bordejo = 40;
gnc_par.T = 0;
gnc_par.e = [];
gnc_par.d_p1_vec = [];
gnc_par.conte = 1;
gnc_par.p0 = [];
gnc_par.p1 = [];
gnc_par.init = 0;
gnc_par.tack = 0;
gnc_par.gamma_aw = 0;
gnc_par.gamma_tw = 0;
gnc_par.psi_t = 0;

gnc_par.err_acc = 0;
gnc_par.init_err = 0;
gnc_par.last_psi_d = 0;
gnc_par.err = [];
gnc_par.cont_err = 1;

gnc_par.Vd = [];
gnc_par.Vd_count = 1;

%LOS parameters
gnc_par.R = 20;

% MODEL PARAMETERS
global mdl_par                                                       
mdl_par.m = 25900;                         % (kg),mass of the vehicle

mdl_par.Ixx = 133690;
mdl_par.Izz = 24760;
mdl_par.Ixz = 2180;                        % moment of inertia

mdl_par.a11 = 970;
mdl_par.a22 = 17430;
mdl_par.a44 = 106500;
mdl_par.a66 = 101650;
mdl_par.a24 = -13160;
mdl_par.a26 = -6190;
mdl_par.a46 = 4730;                        % (kg),added mass coef.  

mdl_par.rho_w = 1025;                      % (kg/m^3), water density                                                                                
mdl_par.rho_a = 1.2;                       % (kg/m^3), air density                  

mdl_par.As = 170;                          % (m^2), sail area                       
mdl_par.h0 = 0.0005;                       % (m), roughness height                  
mdl_par.h1 = 11.58;                        % (m), reference height                  
mdl_par.z_s = -11.58;                      % (m), (x,y,z) is the CoE                
mdl_par.xs = 0;
mdl_par.ys = 0;
mdl_par.zs = -11.58;                       % (m), (x,y,z) is the CoE                
mdl_par.Xce = 0.6;                         % (m), distance along the mast to the CoE
mdl_par.Xm = 0.3;                          % (m), x-coordinate of the mast          
mdl_par.V_aw = 0;
mdl_par.alpha_aw = 0;
mdl_par.alpha_s = 0;
mdl_par.delta_s = 0;

mdl_par.Ar = 1.17;                         % (m^2), rudder area                     
mdl_par.d_r = 1.9;                         % rudder draft                           
mdl_par.zeta_r = 0.8;                      % rudder efficiency                      
mdl_par.x_r = -8.2;
mdl_par.z_r = -0.78;                       % (m), (x,y,z) is the CoE                
mdl_par.xr = -8.2;
mdl_par.yr = 0;
mdl_par.zr = -0.78;                        % (m), (x,y,z) is the CoE                
mdl_par.V_ar = 0;
mdl_par.alpha_ar = 0;
mdl_par.alpha_a = 0;
mdl_par.delta_r = 0;
                                                                                
mdl_par.Ak = 8.7;                          % (m^2), keel area                       
mdl_par.d_k = 2.49;                        % keel draft                             
mdl_par.zeta_k = 0.7;                      % keel efficiency                        
mdl_par.x_k = 0;
mdl_par.z_k = -0.58;                       % (m), (x,y,z) is the CoE                
mdl_par.xk = 0;
mdl_par.yk = 0;
mdl_par.zk = -0.58;                        % (m), (x,y,z) is the CoE                
                                                                                
mdl_par.x_h = 0;
mdl_par.z_h = -1.18;                       % (m), (x,y,z) is the CoE                
mdl_par.xh = 0;
mdl_par.yh = 0;
mdl_par.zh = -1.18;                        % (m), (x,y,z) is the CoE                
                                                                                
mdl_par.w_c = 60000;                       % (N), crew weight 20000                 
mdl_par.x_c = -8;                          % (m), crew position                     
mdl_par.y_bm = 3.6;                        % (m), yacht beam                        
                                                                                
mdl_par.a = -5.89;
mdl_par.b = 8160;
mdl_par.c = 120000;
mdl_par.d = 50000;
