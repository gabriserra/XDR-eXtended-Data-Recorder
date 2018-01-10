function [AV, MAX, MIN] = computeRate(unfilled)
    %unfilled = readFile(filename);
    %unfilled(:,3) = denoise(unfilled(:,3));
    %unfilled(:,4) = denoise(unfilled(:,4));
    %unfilled(:,5) = denoise(unfilled(:,5));
    
    loss = computeLossPackets(unfilled)
    
    unfilled(:,3) = denoise(unfilled(:,3));
    unfilled(:,4) = denoise(unfilled(:,4));
    unfilled(:,5) = denoise(unfilled(:,5));
    
    filled = filler(unfilled);
    
    %vel = iomega(filled, 0.02, 3, 2);
    
    %figure;
    %plot(vel);
    
    var = filled;

    diff = zeros(size(var,1), 1);
    counter = 0;

    for i = 2 : size(var,1)
        if(var(i,2) - var(i-1,2) == 1)
            diff(i) = var(i,1) - var(i-1,1);
        else
            diff(i) = 0;
            counter = counter + 1;
        end
    end

    AV = mean(diff(diff>0));
    
    MIN = min(diff(diff>0));
    
    MAX = max(diff(diff>0));

    figure;
    plot(diff);
end