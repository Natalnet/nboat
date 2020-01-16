theta = 0:0.01:2*pi;
for i = 0.1:0.1:2
    rho = (pi/2)*((cos(theta+pi)+1)/2)*i;
    polarplot(theta,rho);
    hold on;
end