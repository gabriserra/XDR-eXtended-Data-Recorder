function loss = computeLossPackets(unfilled)
    diff = zeros(size(unfilled,1), 4);
    duration = unfilled(size(unfilled,1),1) - unfilled(1,1);
    
    for i = 2 : size(unfilled,1)
        diff(i,1) = unfilled(i,2) - unfilled(i-1,2);
        if(diff(i,1) > 1)
            diff(i,2) = (unfilled(i,1) - unfilled(i-1,1));
            diff(i,3) = unfilled(i-1,1);
            diff(i,4) = unfilled(i,1);
        end
    end
    
    loss = diff(diff(:,1) > 1,:);
    if (~isempty(loss))
        loss = [loss; max(loss(:,1)) min(loss(:,1)) mean(loss(:,1)) 0];
        loss = [loss; sum(loss)];
        loss(size(loss,1), 3:4) = [duration loss(size(loss,1),2)/duration*100];
    end
end