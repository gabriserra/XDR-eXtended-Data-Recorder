function [AV, MAX, MIN, loss] = computeRate(filename)
    unfilled = readFile(filename);
    
    % [var, d] = readFile('../server/log/log_2018-01-06_18-35-50.csv');
%     unfilled = readFile(filename);
    
    loss = computeLossPackets(unfilled);
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
    
    var = unfilled;

    diff = zeros(size(var,1), 1);

    for i = 2 : size(var,1)
        diff(i) = var(i,1) - var(i-1,1);
%         if(var(i,2) - var(i-1,2) == 1)
%             diff(i) = var(i,1) - var(i-1,1);
%         else
%             diff(i) = 0;
%             counter = counter + 1;
%         end
    end

    AV = mean(diff(diff>0));
    
    MIN = min(diff(diff>0));
    
    MAX = max(diff(diff>0));

    figure;
    plot(diff);
end