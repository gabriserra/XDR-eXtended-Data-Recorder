filled = filler(var());
accx = filled(:,3)
accx_filtered = denoise(accx);
filled = filled(:,2:5);

