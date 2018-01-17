%max_accfren
acc_start=176;
acc_interval=17;
brake_start = 213;
brake_interval = 37; 

acc_threshold = 0.04;
brake_threshold = -0.1;
width = 1.5;
figure;
plot(trip(1:450,3),'LineWidth',width,'Color',[0 0 .701]);
hold on
%hline(0,'black');
txt1 = 'acceleration threshold';
t=text(3,0.08,txt1)
t.FontSize=11;
plot([0 450],[acc_threshold acc_threshold],'r--','LineWidth',width);
hold on;
txt1 = 'braking threshold';
t= text(325,-0.13,txt1)
t.FontSize=11;
plot([0 450],[brake_threshold brake_threshold],'r--','LineWidth',width);
hold on; 
plot(acc_start-1:acc_start+acc_interval,trip(acc_start-1:acc_start+acc_interval,3),'LineWidth',width,'Color',[.31 .58 .26]);
hold on;
plot(brake_start-1:brake_start+brake_interval,trip(brake_start-1:brake_start+brake_interval,3),'LineWidth',width,'Color',[.31 .58 .26]);