subtrip = kicks;
subtrip2 = kicks15;
subtrip3 =turn_norm;
subtrip4 = turns2;
subtrip5 = longtrip3;
subtrip6 = longtrip2;

noise_subtrip = filler(kicks);
noise_subtrip2=filler(kicks15);
noise_subtrip3=filler(turn_norm)
noise_subtrip4=filler(turns2);
noise_subtrip5 = filler(longtrip3);
noise_subtrip6 = filler(longtrip2);

for i=3:1:5
     subtrip(:,i) = denoise(subtrip(:,i));
      subtrip2(:,i) = denoise(subtrip2(:,i));
      subtrip3(:,i) = denoise(subtrip3(:,i));
      subtrip4(:,i)= denoise(subtrip4(:,i));
     subtrip5(:,i) = denoise(subtrip5(:,i));
     subtrip6(:,i) = denoise(subtrip6(:,i));
     
end
 
 var_subtrip = filler(subtrip);
 ylimits = size(var_subtrip,1)

 var_subtrip2=filler(subtrip2);
 ylimits = [ylimits ; size(var_subtrip2,1)]

 var_subtrip3=filler(subtrip3);
 ylimits = [ylimits ;size(var_subtrip3,1)]

 var_subtrip4=filler(subtrip4);
 ylimits= [ylimits ;size(var_subtrip4,1)]

 var_subtrip5 = filler(subtrip5);
 ylimits = [ylimits ;size(var_subtrip5,1)];
 
 var_subtrip6 = filler(subtrip6);
 ylimits = [ylimits ;size(var_subtrip6,1)];


for i=2:1:size(ylimits,1)
    ylimits(i,1) =  ylimits(i-1,1)+ylimits(i,1);
end


 
 trip= var_subtrip;
  trip = [trip; var_subtrip2(:,1)  (var_subtrip2(:,2)+trip(size(trip,1),2)) var_subtrip2(:,3) var_subtrip2(:,4) var_subtrip2(:,5)];
 trip = [trip;  var_subtrip3(:,1)  ( var_subtrip3(:,2)+trip(size(trip,1),2))  var_subtrip3(:,3)  var_subtrip3(:,4)  var_subtrip3(:,5)];
 trip = [trip; var_subtrip4(:,1)  (var_subtrip4(:,2)+trip(size(trip,1),2)) var_subtrip4(:,3) var_subtrip4(:,4) var_subtrip4(:,5)];
 trip = [trip; var_subtrip5(:,1)  (var_subtrip5(:,2)+trip(size(trip,1),2)) var_subtrip5(:,3) var_subtrip5(:,4) var_subtrip5(:,5)];
 trip = [trip; var_subtrip6(:,1)  (var_subtrip6(:,2)+trip(size(trip,1),2)) var_subtrip6(:,3) var_subtrip6(:,4) var_subtrip6(:,5)];

 n_trip= noise_subtrip;
 n_trip = [n_trip; noise_subtrip2(:,1)  (noise_subtrip2(:,2)+n_trip(size(n_trip,1),2)) noise_subtrip2(:,3) noise_subtrip2(:,4) noise_subtrip2(:,5)];
 n_trip = [n_trip;  noise_subtrip3(:,1)  ( noise_subtrip3(:,2)+n_trip(size(n_trip,1),2))  noise_subtrip3(:,3)  noise_subtrip3(:,4)  noise_subtrip3(:,5)];
 n_trip = [n_trip; noise_subtrip4(:,1)  (noise_subtrip4(:,2)+n_trip(size(n_trip,1),2)) noise_subtrip4(:,3) noise_subtrip4(:,4) noise_subtrip4(:,5)];
 n_trip = [n_trip; noise_subtrip5(:,1)  (noise_subtrip5(:,2)+n_trip(size(n_trip,1),2)) noise_subtrip5(:,3) noise_subtrip5(:,4) noise_subtrip5(:,5)];
 n_trip = [n_trip; noise_subtrip6(:,1)  (noise_subtrip6(:,2)+n_trip(size(n_trip,1),2)) noise_subtrip6(:,3) noise_subtrip6(:,4) noise_subtrip6(:,5)];


var=trip;
n_var=n_trip;

figure;
plot(n_var(:,3),'r');
hold on;
plot(var(:,3));
hold on; 
vline(ylimits','g')

figure;
plot(var(:,4));
vline(ylimits','g')

figure;
plot(var(:,5));
vline(ylimits','g')


%plot(var(:,3),'r')
[suddens, turns, static_crashes, dynamic_crashes]=main_checker(var,n_var);
zsuddens=suddens; 
zturns=turns;
zstatic_crashes=static_crashes;
zdynamic_crashes=dynamic_crashes;