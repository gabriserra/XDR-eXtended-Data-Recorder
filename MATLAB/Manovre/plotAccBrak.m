%max_accfren
acc_start=176;
acc_interval=17;
brake_start = 213;
brake_interval = 37; 

acc_threshold = 0.04;
brake_threshold = -0.1;
width = 2;
figure;
plot(trip(150:300,3),'LineWidth',width,'Color',[0 0 .701]);
hold on
%hline(0,'black');
txt1 = 'acceleration threshold';
t=text(3,0.08,txt1)
t.FontSize=12;
plot([0 150],[acc_threshold acc_threshold],'r--','LineWidth',width);
hold on;
txt1 = 'braking threshold';
t= text(120,-0.13,txt1)
t.FontSize=12;
plot([0 150],[brake_threshold brake_threshold],'r--','LineWidth',width);
hold on; 
plot(acc_start-1-149:acc_start+acc_interval-149,trip(acc_start-1:acc_start+acc_interval,3),'g','LineWidth',width);
hold on;
plot(brake_start-1-149:brake_start+brake_interval-149,trip(brake_start-1:brake_start+brake_interval,3),'g','LineWidth',width);