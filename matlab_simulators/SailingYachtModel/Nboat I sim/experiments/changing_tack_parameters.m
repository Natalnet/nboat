close all;
% figure;
tempos = [0 0 0];
set_param('sailboatModel/PI heading controller/Kp', 'Value' , num2str(5));
set_param('sailboatModel/PI heading controller/Ki', 'Value' , num2str(2));
for i=1:2
subplot(1,2,i);
%subplot(2,2,[(i*2)-1 i*2]);
set(gca, 'FontSize', 14, 'LineWidth', 1);
angstring = strcat('[0;0;0;',num2str(deg2rad(0)), ';3;0;0;0]');
set_param('sailboatModel/IC', 'Value' , angstring);
set_param('sailboatModel/4DOF nonlinear sailing yacht model/vento', 'Value', num2str(deg2rad(-180)));
% xlabel('x[m]');
% xlabel('y[m]');

if i == 1
    tic;
    set_param('sailboatModel/controleTraj/distBord', 'Value' , num2str(30));
    set_param('sailboatModel/controleTraj/angBord', 'Value' , num2str(30));
    sim('sailboatModel');
    tempo(i) = toc;
    ylabel('y[m]');
    xlabel('x[m]');
end
if i == 2
    tic;
    set_param('sailboatModel/controleTraj/distBord', 'Value' , num2str(30));
    set_param('sailboatModel/controleTraj/angBord', 'Value' , num2str(50));
    sim('sailboatModel');
    ylabel('y[m]');
    xlabel('x[m]');
    tempo(i) = toc;
%     drawArrow = @(x,y,varargin) quiver( x(1),y(1),x(2)-x(1),y(2)-y(1),0, varargin{:});
%     drawArrow([490 480],[-20 -20],'linewidth',1,'color','black'); hold on;
%     drawArrow([490 480],[-10 -10],'linewidth',1,'color','black');
%     drawArrow([490 480],[-30 -30],'linewidth',1,'color','black');   
end
if i == 3
    tic;
    set_param('sailboatModel/controleTraj/distBord', 'Value' , num2str(50));
    set_param('sailboatModel/controleTraj/angBord', 'Value' , num2str(70));
    sim('sailboatModel');
    tempo(i) = toc;
end
if i == 4
    set_param('sailboatModel/controleTraj/distBord', 'Value' , num2str(100));
    set_param('sailboatModel/controleTraj/angBord', 'Value' , num2str(50));
    sim('sailboatModel');
end 
hold on;
plot(X.signals.values(:,2), X.signals.values(:,1), 'b', 'LineWidth', 1.5);
[l,c] = size(par.pontos_bordejar);
pbstst = zeros(l,c+1);
pbstst(:,2:c+1) = par.pontos_bordejar(:,1:c);
[lpb, cpb] = size(pbstst);
for contPlot = 2:cpb-1
   plot(pbstst(2,contPlot), pbstst(1,contPlot),'blacko', 'LineWidth', 2); 
end
plot(0,0, 'black.', 'MarkerSize', 30, 'LineWidth', 3.5);
plot(0, 200, 'blackx', 'MarkerSize', 14, 'LineWidth', 1.5);
axis tight;
[l,c] = size(X.time);
tempos(i) = X.time(l,1);
grid on;
end
% ylabel('y[m]');
% figure;
% [l,c] = size(X.time);
% lasttime = X.time(l,1);
% [l,c] = size(par.spvec);
% plot(0:lasttime/(c-1):lasttime,par.spvec);
% hold on;
% plot([0 lasttime], [1 1],'r');
% hold off;
