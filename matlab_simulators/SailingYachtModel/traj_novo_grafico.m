clear;
close all;
% figure;
tempos = [0 0 0];
hold on;
for i=1:3
%subplot(3,2,[(i*2)-1 i*2]);
%subplot(2,2,[(i*2)-1 i*2]);
set(gca, 'FontSize', 14, 'LineWidth', 1);
% xlabel('x[m]');
% xlabel('y[m]');
set_param('SailingYachtModel/4DOF nonlinear sailing yacht model/vento', 'Value', num2str(deg2rad(-90)));
angstring = strcat('[0;0;0;',num2str(deg2rad(-90)), ';3;0;0;0]');
set_param('SailingYachtModel/IC', 'Value' , angstring);
if i == 1
    set_param('SailingYachtModel/simple P heading controller/Kp', 'Value' , num2str(1));
    set_param('SailingYachtModel/simple P heading controller/Ki', 'Value' , num2str(0));
    sim('SailingYachtModel');
    [l, c] = size(X.signals.values);
    cont2 = 1;
    for cont1 = 1:l
        if mod(cont1,4) == 0
            aux(cont2,:) = X.signals.values(cont1,:);
            cont2 = cont2+1;
        end
    end
    aux(cont2,:) = X.signals.values(l,:);
%     p1 = plot(X.signals.values(:,2), X.signals.values(:,1), '-ko' ,'LineWidth', 2);
    p1 = plot(aux(:,2), aux(:,1), '-ko' ,'LineWidth', 1.5);
end
if i == 2
    set_param('SailingYachtModel/simple P heading controller/Kp', 'Value' , num2str(1));
    set_param('SailingYachtModel/simple P heading controller/Ki', 'Value' , num2str(14));
    sim('SailingYachtModel');
    p2 = plot(X.signals.values(:,2), X.signals.values(:,1), 'k-.' ,'LineWidth', 1.5);
    ylabel('y[m]');
%     drawArrow = @(x,y,varargin) quiver( x(1),y(1),x(2)-x(1),y(2)-y(1),0, varargin{:});
%     drawArrow([490 480],[-20 -20],'linewidth',1,'color','black'); hold on;
%     drawArrow([490 480],[-10 -10],'linewidth',1,'color','black');
%     drawArrow([490 480],[-30 -30],'linewidth',1,'color','black');   
end
if i == 3
    set_param('SailingYachtModel/simple P heading controller/Kp', 'Value' , num2str(10.5));
    set_param('SailingYachtModel/simple P heading controller/Ki', 'Value' , num2str(20));
    sim('SailingYachtModel');
    p3 = plot(X.signals.values(:,2), X.signals.values(:,1), 'k','LineWidth', 1.5);
end
% if i == 4
%     set_param('SailingYachtModel/controleTraj/distBord', 'Value' , num2str(100));
%     set_param('SailingYachtModel/controleTraj/angBord', 'Value' , num2str(50));
%     sim('SailingYachtModel');
% end 
p4 = plot([-15, -15], [0 100], 'k--', 'LineWidth', 2.5);
p5 = plot([15, 15], [0 100], 'k--', 'LineWidth', 2.5);
hold on;
[l,c] = size(par.pontos_bordejar);
pbstst = zeros(l,c+1);
pbstst(:,2:c+1) = par.pontos_bordejar(:,1:c);
[lpb, cpb] = size(pbstst);
for contPlot = 2:cpb-1
   p6 = plot(pbstst(1,contPlot),pbstst(2,contPlot) ,'blacko', 'LineWidth', 2); 
end
% plot(0,0, 'black.', 'MarkerSize', 14, 'LineWidth', 1.5);
p7 = plot(0,100, 'blackx', 'MarkerSize', 14, 'LineWidth', 1.5);
p8 = plot(0,0, 'black.', 'MarkerSize', 36, 'LineWidth', 7.5);
%axis([-60,60,-20,100]);
axis equal;
[l,c] = size(X.time);
tempos(i) = X.time(l,1);
grid;
end
xlabel('x[m]');
%legend([p1, p2, p3, p4, p7],'Kp = 1, Ki = 0','Kp = 1, Ki = 14', 'Kp = 1.5, Ki = 20', 'Limites', 'Ponto alvo')
legend([p1, p2, p3, p4, p7, p8],'P','Static PI', 'GS-PI ', 'Safe zone', 'Target', 'Start');
% figure;
% [l,c] = size(X.time);
% lasttime = X.time(l,1);
% [l,c] = size(par.spvec);
% plot(0:lasttime/(c-1):lasttime,par.spvec);
% hold on;
% plot([0 lasttime], [1 1],'r');
% hold off;
