function loss = computeLossPackets(unfilled)
    diff = zeros(size(unfilled,1), 4);
    
    for i = 2 : size(unfilled,1)
        diff(i,1) = unfilled(i,2) - unfilled(i-1,2);
        if(diff(i,1) > 1)
            diff(i,2) = (unfilled(i,1) - unfilled(i-1,1)) / 1000;
            diff(i,3) = unfilled(i-1,1) / 1000;
            diff(i,4) = unfilled(i,1) / 1000;
        end
    end
    
    loss = diff(diff(:,1) > 1,:);
    loss = [loss; sum(loss)];
    loss(size(loss,1), 3:4) = [0 0];
end