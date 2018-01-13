subtrip = crash_K2;
subtrip2 = acc_fren2;
subtrip3 = max2;
subtrip4 = good2;
subtrip5 = crash_C2;

for i=3:1:5
    i_subtrip2(:,i) = denoise(subtrip2(:,i));
    i_subtrip5(:,i) = denoise(subtrip5(:,i));
    i_subtrip3(:,i) = denoise(subtrip3(:,i))
    i_subtrip4(:,i)= denoise(subtrip4(:,i));
   % subtrip(:,i) = denoise(subtrip(:,i));
end

 noise_subtrip = filler(subtrip);
 noise_subtrip2=filler(i_subtrip2);
 noise_subtrip3=filler( i_subtrip3);
 noise_subtrip4=filler( i_subtrip4);
 noise_subtrip5 = filler(i_subtrip5);
 
 var_subtrip = filler(subtrip);
 var_subtrip2=filler(i_subtrip2);
 var_subtrip3=filler( i_subtrip3);
 var_subtrip4=filler( i_subtrip4);
 var_subtrip5 = filler(i_subtrip5);

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


xlimits=[size(var_subtrip,1) size(var_subtrip,1) size(var_subtrip,1)+size(var_subtrip2,1) size(var_subtrip,1)+size(var_subtrip2,1)  ];
ylimits=[-2 2 -2 2];
figure;
plot(var(:,3));
% hold on;
% plot(xlimits,ylimits,'r')

%plot( size(var_subtrip,1) ,size(var_subtrip,1),-1.5,1.5);

figure;
plot(var(:,4));
% hold on;
% plot(xlimits,ylimits,'r')
figure;
plot(var(:,5));
% hold on;
% plot(xlimits,ylimits,'r')

%plot(var(:,3),'r')