%urto153
start=375;
interval=7;

acc_threshold = 0.04;
brake_threshold = -0.1;
figure;
plot(0:425,trip(50:475,3),'LineWidth',1);
%hline(0,'black');
txt1 = 'dynamic crash threshold';
t=text(3,-0.13,txt1)
t.FontSize=11;
% hline(acc_threshold,'r');
% txt1 = 'braking threshold';
% t= text(325,-0.13,txt1)
% t.FontSize=11;
hline(brake_threshold,'r');
hold on; 
plot(start-1-50:start+interval-50,trip(start-1:start+interval,3),'g','LineWidth',1);
