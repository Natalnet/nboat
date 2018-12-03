close all;
% figure;
tempos = [0 0 0];
for i=1:3
subplot(3,2,[(i*2)-1 i*2]);
%subplot(2,2,[(i*2)-1 i*2]);
set(gca, 'FontSize', 14, 'LineWidth', 1);
% xlabel('x[m]');
% xlabel('y[m]');
angstring = strcat('[0;0;0;',num2str(deg2rad(90)), ';3;0;0;0]');
set_param('SailingYachtModel/IC', 'Value' , angstring);
set_param('SailingYachtModel/4DOF nonlinear sailing yacht model/vento', 'Value', num2str(deg2rad(135)));
if i == 1
    set_param('SailingYachtModel/simple P heading controller/Kp', 'Value' , num2str(1));
    set_param('SailingYachtModel/simple P heading controller/Ki', 'Value' , num2str(0));
    sim('SailingYachtModel');
end
if i == 2
    set_param('SailingYachtModel/simple P heading controller/Kp', 'Value' , num2str(2));
    set_param('SailingYachtModel/simple P heading controller/Ki', 'Value' , num2str(5));
    sim('SailingYachtModel');
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
end
% if i == 4
%     set_param('SailingYachtModel/controleTraj/distBord', 'Value' , num2str(100));
%     set_param('SailingYachtModel/controleTraj/angBord', 'Value' , num2str(50));
%     sim('SailingYachtModel');
% end 
hold on;
plot(X.signals.values(:,1), X.signals.values(:,2),'r', 'LineWidth', 1.5);
[l,c] = size(par.pontos_bordejar);
pbstst = zeros(l,c+1);
pbstst(:,2:c+1) = par.pontos_bordejar(:,1:c);
[lpb, cpb] = size(pbstst);
for contPlot = 2:cpb-1
   plot(pbstst(1,contPlot),pbstst(2,contPlot) ,'blacko', 'LineWidth', 2); 
end
% plot(0,0, 'black.', 'MarkerSize', 14, 'LineWidth', 1.5);
plot(100,0, 'blackx', 'MarkerSize', 8, 'LineWidth', 1.5);
axis tight;
[l,c] = size(X.time);
tempos(i) = X.time(l,1);
grid;
end
xlabel('x[m]');
% figure;
% [l,c] = size(X.time);
% lasttime = X.time(l,1);
% [l,c] = size(par.spvec);
% plot(0:lasttime/(c-1):lasttime,par.spvec);
% hold on;
% plot([0 lasttime], [1 1],'r');
% hold off;
