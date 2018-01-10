var=data2;
for i=3:1:size(var,2)
    var(:,i) = denoise(var(:,i));
end

var=filler(var);
var=var(:,2:5);