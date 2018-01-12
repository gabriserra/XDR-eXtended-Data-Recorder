function filled = computeDate(filled, date)
    start_time = datetime(date,'InputFormat','uuuu-MM-dd_HH-mm-ss');
    timestamp = zeros(size(filled,1),1);
    
    for i = 1 : size(filled,1)
       filled(i,1) = filled(i,1) - filled(1,1);
    end
    
    for i = 1 : size(filled,1)
       timestamp(i) = start_time + milliseconds(filled(i,1));
    end
    
    filled = [timestamp filled(:,2:5)];
end