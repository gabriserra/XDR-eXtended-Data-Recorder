function computeRate(filename)
    % [loss, stats] = computeLossPackets(unfilled);
    %unfilled(:,3) = denoise(unfilled(:,3));
    %unfilled(:,4) = denoise(unfilled(:,4));
    %unfilled(:,5) = denoise(unfilled(:,5));
    
    filled = filler(unfilled);
    
    timestamp = computeDate(filled, erase(erase(filename,'.csv'),'../../server/log/log_'));
    
    figure;
    plot(timestamp, filled(:,3));
    
    %vel = iomega(filled, 0.02, 3, 2);
    
    %figure;
    %plot(vel);

end