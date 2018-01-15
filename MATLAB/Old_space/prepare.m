subtrip = acc;
subtrip2 = good;
subtrip3 = post_kicks;
subtrip4 = max1;
subtrip5 = urto_max;
% subtrip5 = crash_C2;

for i=3:1:5
     subtrip(:,i) = denoise(subtrip(:,i));
     subtrip2(:,i) = denoise(subtrip2(:,i));
     subtrip3(:,i) = denoise(subtrip3(:,i));
     subtrip4(:,i)= denoise(subtrip4(:,i));
     subtrip5(:,i) = denoise(subtrip5(:,i));
     
end

   noise_subtrip = filler(acc);
   noise_subtrip2=filler(good);
   noise_subtrip3=filler(post_kicks);
   noise_subtrip4=filler(max1);
   noise_subtrip5 = filler(urto_max);
 
 var_subtrip = filler(subtrip);
 var_subtrip2=filler(subtrip2);
 var_subtrip3=filler(subtrip3);
 var_subtrip4=filler(subtrip4);
 var_subtrip5 = filler(subtrip5);

 %plot(var_acc_fren2(:,3),'r')
 

trip= var_subtrip;
%trip = [trip; var_subtrip(:,1) (var_subtrip(:,2)+trip(size(trip,1),2)) var_subtrip(:,3) var_subtrip(:,4) var_subtrip(:,5)];
 trip = [trip; var_subtrip2(:,1)  (var_subtrip2(:,2)+trip(size(trip,1),2)) var_subtrip2(:,3) var_subtrip2(:,4) var_subtrip2(:,5)];
 trip = [trip;  var_subtrip3(:,1)  ( var_subtrip3(:,2)+trip(size(trip,1),2))  var_subtrip3(:,3)  var_subtrip3(:,4)  var_subtrip3(:,5)];
 trip = [trip; var_subtrip4(:,1)  (var_subtrip4(:,2)+trip(size(trip,1),2)) var_subtrip4(:,3) var_subtrip4(:,4) var_subtrip4(:,5)];
 trip = [trip; var_subtrip5(:,1)  (var_subtrip5(:,2)+trip(size(trip,1),2)) var_subtrip5(:,3) var_subtrip5(:,4) var_subtrip5(:,5)];


 n_trip= noise_subtrip;
 n_trip = [n_trip; noise_subtrip2(:,1)  (noise_subtrip2(:,2)+n_trip(size(n_trip,1),2)) noise_subtrip2(:,3) noise_subtrip2(:,4) noise_subtrip2(:,5)];
 n_trip = [n_trip;  noise_subtrip3(:,1)  ( noise_subtrip3(:,2)+n_trip(size(n_trip,1),2))  noise_subtrip3(:,3)  noise_subtrip3(:,4)  noise_subtrip3(:,5)];
 n_trip = [n_trip; noise_subtrip4(:,1)  (noise_subtrip4(:,2)+n_trip(size(n_trip,1),2)) noise_subtrip4(:,3) noise_subtrip4(:,4) noise_subtrip4(:,5)];
 n_trip = [n_trip; noise_subtrip5(:,1)  (noise_subtrip5(:,2)+n_trip(size(n_trip,1),2)) noise_subtrip5(:,3) noise_subtrip5(:,4) noise_subtrip5(:,5)];
% 
% 
% xlimits=[size(var_subtrip,1) size(var_subtrip,1) size(var_subtrip,1)+size(var_subtrip2,1) size(var_subtrip,1)+size(var_subtrip2,1)  ];
% ylimits=[-2 2 -2 2];
var=trip;
n_var=n_trip;
figure;
plot(n_var(:,3),'r');
hold on;
plot(var(:,3));

% hold on;
% plot(xlimits,ylimits,'r')

%plot( size(var_subtrip,1) ,size(var_subtrip,1),-1.5,1.5);
var = trip;
figure;
plot(var(:,4));
% hold on;
% plot(xlimits,ylimits,'r')
figure;
plot(var(:,5));
% hold on;
% plot(xlimits,ylimits,'r')

%plot(var(:,3),'r')
[suddens, turns, static_crashes, dynamic_crashes]=main_checker(var,n_var);
zsuddens=suddens; 
zturns=turns;
zstatic_crashes=static_crashes;
zdynamic_crashes=dynamic_crashes;