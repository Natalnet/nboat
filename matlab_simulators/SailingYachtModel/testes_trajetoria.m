% close all;
% sim('SailingYachtModel')
% plot(X.signals.values(:,2), X.signals.values(:,1),'r', 'LineWidth', 1.5);
% hold on;
% plot([-60, -60], [0 100], 'k.', 'LineWidth', 1.5);
% plot([60, 60], [0 100], 'k.', 'LineWidth', 1.5);
% grid;

fid = fopen('arquivo2.txt','wt')
fprintf(fid,'%f, ',angulo_leme)
fclose(fid)