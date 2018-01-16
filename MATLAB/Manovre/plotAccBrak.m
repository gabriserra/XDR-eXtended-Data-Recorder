%max_accfren
acc_start=176;
acc_interval=17;
brake_start = 213;
brake_interval = 37; 

acc_threshold = 0.04; brake_threshold = -0.1;
figure;
plot(trip(1:450,3),'LineWidth',1);
%hline(0,'black');
txt1 = 'acceleration threshold';
t=text(3,0.08,txt1)
t.FontSize=11;
hline(acc_threshold,'r');
txt1 = 'braking threshold';
t= text(325,-0.13,txt1)
t.FontSize=11;
hline(brake_threshold,'r');
hold on; 
plot(acc_start-1:acc_start+acc_interval,trip(acc_start-1:acc_start+acc_interval,3),'g','LineWidth',1);
hold on;
plot(brake_start-1:brake_start+brake_interval,trip(brake_start-1:brake_start+brake_interval,3),'g','LineWidth',1);