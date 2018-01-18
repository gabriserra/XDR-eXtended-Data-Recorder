%kicks15
start=411;
interval=1;
start2 = 541;
interval2 = 1; 
start3 = 751;
interval3 = 1; 
start4 = 852;
interval4 = 1;
acc_threshold = 0.04; 
brake_threshold = -0.1;
figure;
width=1.5;
plot(n_trip(250:size(n_trip,1),3),'LineWidth',width,'Color',[0 0 .701]);
hold on;
%hline(0,'black');
txt1 = 'rear crash';
t=text(3,1.65,txt1)
t.FontSize=11;
plot([0 size(n_trip,1)-250],[1.5 1.5],'r--','LineWidth',width);
hold on;
txt1 = 'front crash';
t= text(3,-1.65,txt1)
t.FontSize=11;
plot([0 size(n_trip,1)-250],[-1.5 -1.5],'r--','LineWidth',width);
hold on; 
plot(start-250:start+interval-250+1,n_trip(start-1:start+interval,3),'g','LineWidth',width);
hold on;
plot(start2-250:start2+interval2-250+1,n_trip(start2-1:start2+interval2,3),'g','LineWidth',width);
hold on;
plot(start3-250:start3+interval3-250+1,n_trip(start3-1:start3+interval3,3),'g','LineWidth',width);
hold on;
plot(start4-250:start4+interval4-250+1,n_trip(start4-1:start4+interval4,3),'g','LineWidth',1);