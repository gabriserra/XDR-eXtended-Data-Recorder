subtrip = acc_fren;
subtrip2 = acc;
subtrip3 = curva_bad;
 subtrip4 = urto_wall;
 subtrip5 = sx_kicks;
 subtrip6 = ant_kicks;
% subtrip7 = urto_wall;
% subtrip5 = crash_C2;

for i=3:1:5
     subtrip(:,i) = denoise(subtrip(:,i));
     subtrip2(:,i) = denoise(subtrip2(:,i));
     subtrip3(:,i) = denoise(subtrip3(:,i));
      subtrip4(:,i)= denoise(subtrip4(:,i));
      subtrip5(:,i) = denoise(subtrip5(:,i));
      subtrip6(:,i) = denoise(subtrip6(:,i));
%      subtrip7(:,i) = denoise(subtrip7(:,i));
     
end

   noise_subtrip = filler(acc_fren);
   noise_subtrip2=filler(acc);
   noise_subtrip3=filler(curva_bad);
    noise_subtrip4=filler(urto_wall);
    noise_subtrip5 = filler(sx_kicks);
    noise_subtrip6 = filler(ant_kicks);
%    noise_subtrip7 = filler(urto_wall);
 
 var_subtrip = filler(subtrip);
 var_subtrip2=filler(subtrip2);
 var_subtrip3=filler(subtrip3);
  var_subtrip4=filler(subtrip4);
  var_subtrip5 = filler(subtrip5);
  var_subtrip6 = filler(subtrip5);
%  var_subtrip7 = filler(subtrip5);

 %plot(var_acc_fren2(:,3),'r')
 

trip= var_subtrip;
%trip = [trip; var_subtrip(:,1) (var_subtrip(:,2)+trip(size(trip,1),2)) var_subtrip(:,3) var_subtrip(:,4) var_subtrip(:,5)];
  trip = [trip; var_subtrip2(:,1)  (var_subtrip2(:,2)+trip(size(trip,1),2)) var_subtrip2(:,3) var_subtrip2(:,4) var_subtrip2(:,5)];
  trip = [trip;  var_subtrip3(:,1)  ( var_subtrip3(:,2)+trip(size(trip,1),2))  var_subtrip3(:,3)  var_subtrip3(:,4)  var_subtrip3(:,5)];
  trip = [trip; var_subtrip4(:,1)  (var_subtrip4(:,2)+trip(size(trip,1),2)) var_subtrip4(:,3) var_subtrip4(:,4) var_subtrip4(:,5)];
 trip = [trip; var_subtrip5(:,1)  (var_subtrip5(:,2)+trip(size(trip,1),2)) var_subtrip5(:,3) var_subtrip5(:,4) var_subtrip5(:,5)];
  trip = [trip; var_subtrip6(:,1)  (var_subtrip6(:,2)+trip(size(trip,1),2)) var_subtrip6(:,3) var_subtrip6(:,4) var_subtrip6(:,5)];
%  trip = [trip; var_subtrip7(:,1)  (var_subtrip7(:,2)+trip(size(trip,1),2)) var_subtrip7(:,3) var_subtrip7(:,4) var_subtrip7(:,5)];


 n_trip= noise_subtrip;
  n_trip = [n_trip; noise_subtrip2(:,1)  (noise_subtrip2(:,2)+n_trip(size(n_trip,1),2)) noise_subtrip2(:,3) noise_subtrip2(:,4) noise_subtrip2(:,5)];
  n_trip = [n_trip;  noise_subtrip3(:,1)  ( noise_subtrip3(:,2)+n_trip(size(n_trip,1),2))  noise_subtrip3(:,3)  noise_subtrip3(:,4)  noise_subtrip3(:,5)];  n_trip = [n_trip; noise_subtrip4(:,1)  (noise_subtrip4(:,2)+n_trip(size(n_trip,1),2)) noise_subtrip4(:,3) noise_subtrip4(:,4) noise_subtrip4(:,5)];
  n_trip = [n_trip; noise_subtrip5(:,1)  (noise_subtrip5(:,2)+n_trip(size(n_trip,1),2)) noise_subtrip5(:,3) noise_subtrip5(:,4) noise_subtrip5(:,5)];
  n_trip = [n_trip; noise_subtrip6(:,1)  (noise_subtrip6(:,2)+n_trip(size(n_trip,1),2)) noise_subtrip6(:,3) noise_subtrip6(:,4) noise_subtrip6(:,5)];
%  n_trip = [n_trip; noise_subtrip7(:,1)  (noise_subtrip7(:,2)+n_trip(size(n_trip,1),2)) noise_subtrip7(:,3) noise_subtrip7(:,4) noise_subtrip7(:,5)];
   
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