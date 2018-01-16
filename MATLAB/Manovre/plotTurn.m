%turn_min
start=3131;
interval=81;
start2 = 3369;
interval2=133;


 turn_lower_size = 15;
acc_threshold =0.035;
brake_threshold = -0.1;
figure;
plot(trip(2750:size(trip,1),4),'LineWidth',1);
%hline(0,'black');
txt1 = 'turning threshold';
t=text(20,0.04,txt1)
t.FontSize=11;
hline(acc_threshold,'r');

hold on; 
plot(start-1-2750:start+interval-2750,trip(start-1:start+interval,4),'g','LineWidth',1);
hold on;
plot(start2-1-2750:start2+interval2-2750,trip(start2-1:start2+interval2,4),'g','LineWidth',1);