trip= noise_subtrip;
trip = [trip; noise_subtrip2(:,1)  (noise_subtrip2(:,2)+trip(size(trip,1),2)) noise_subtrip2(:,3) noise_subtrip2(:,4) noise_subtrip2(:,5)];
trip = [trip;  noise_subtrip3(:,1)  ( noise_subtrip3(:,2)+trip(size(trip,1),2))  noise_subtrip3(:,3)  noise_subtrip3(:,4)  noise_subtrip3(:,5)];
trip = [trip; noise_subtrip4(:,1)  (noise_subtrip4(:,2)+trip(size(trip,1),2)) noise_subtrip4(:,3) noise_subtrip4(:,4) noise_subtrip4(:,5)];
trip = [trip; noise_subtrip5(:,1)  (noise_subtrip5(:,2)+trip(size(trip,1),2)) noise_subtrip5(:,3) noise_subtrip5(:,4) noise_subtrip5(:,5)];
