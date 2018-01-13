for i=3:1:5
   var(:,i)= denoise(var(:,i));
   % subtrip(:,i) = denoise(subtrip(:,i));
end
var=filler(var);

figure;
plot(var(:,2),var(:,3));
figure;
plot(var(:,2),var(:,4));
figure;
plot(var(:,2),var(:,5));
% figure;
% plot(var(:,1),var(:,5));
% figure;
% plot(var(:,1),var(:,6));
% figure;
% plot(var(:,1),var(:,7));
% figure;
% plot(var(:,1),var(:,8));