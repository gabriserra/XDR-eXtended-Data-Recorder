i_crash_K2=crash_K2;
i_acc_fren2=acc_fren2;
i_crash_C2=crash_C2;

for i=3:1:5
    i_acc_fren2(:,i) = denoise(i_acc_fren2(:,i));
    i_crash_C2(:,i) = denoise(i_crash_C2(:,i));
end

 noise_crash_K2=filler( crash_K2);
 noise_acc_fren2=filler( acc_fren2);
 noise_crash_C2=filler( crash_C2);
  
 var_crash_C2=filler( i_crash_C2);
 var_crash_K2=filler( i_crash_K2);
 var_acc_fren2=filler( i_acc_fren2);
 %plot(var_acc_fren2(:,3),'r')
 var_crash_C2=filler( i_crash_C2);

trip=var_crash_K2;
trip = [trip; var_acc_fren2(:,1) (var_acc_fren2(:,2)+trip(size(trip,1),2)) var_acc_fren2(:,3) var_acc_fren2(:,4) var_acc_fren2(:,5)];
trip = [trip; var_crash_C2(:,1)  (var_crash_C2(:,2)+trip(size(trip,1),2)) var_crash_C2(:,3) var_crash_C2(:,4) var_crash_C2(:,5)];

n_trip=noise_crash_K2;
n_trip = [n_trip; noise_acc_fren2(:,1) (noise_acc_fren2(:,2)+n_trip(size(n_trip,1),2)) noise_acc_fren2(:,3) noise_acc_fren2(:,4) noise_acc_fren2(:,5)];
n_trip = [n_trip; noise_crash_C2(:,1)  (noise_crash_C2(:,2)+n_trip(size(n_trip,1),2)) noise_crash_C2(:,3) noise_crash_C2(:,4) noise_crash_C2(:,5)];

var=trip;


figure;
plot(var(:,3))
figure;
plot(var(:,4))
figure;
plot(var(:,5))

%plot(var(:,3),'r')