function V_out=ise(V_in)
global gnc_par

psi = V_in(1);
psi_d = V_in(2);

err = psi - psi_d;

gnc_par.err_acc = gnc_par.err_acc + abs(err);

if gnc_par.init_err == 0
    gnc_par.last_psi_d = psi_d;
    gnc_par.init_err = 1;
end

if psi_d ~= gnc_par.last_psi_d
    gnc_par.err(gnc_par.cont_err, 1) = rad2deg(gnc_par.last_psi_d);
    gnc_par.err(gnc_par.cont_err, 2) = rad2deg(psi_d);
    gnc_par.err(gnc_par.cont_err, 3) = gnc_par.err_acc;
    gnc_par.cont_err = gnc_par.cont_err + 1;
    gnc_par.err_acc = 0;
    gnc_par.last_psi_d = psi_d;
end

err_ = gnc_par.err_acc;

V_out = err_;
end