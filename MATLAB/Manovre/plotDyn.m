%urto153
start=375;
interval=7;
width = 1.5;
acc_threshold = -0.05;
brake_threshold = -0.5;
figure;
plot(0:425,trip(50:475,3),'LineWidth',width,'Color',[0 0 .701]);
hold on;
%hline(0,'black');
txt1 = 'dynamic crash upper';
t=text(3,-0.08,txt1)
t.FontSize=11;
plot([0 425],[acc_threshold acc_threshold],'r--','LineWidth',width);
hold on;
txt1 = 'dynamic crash lower';
t= text(3,-0.46,txt1)
t.FontSize=11;
hline(brake_threshold,'r');
plot([0 425],[brake_threshold brake_threshold],'r--','LineWidth',width);
hold on; 
plot(start-1-50:start+interval-50,trip(start-1:start+interval,3),'g','LineWidth',width,'Color',[.31 .58 .26]);