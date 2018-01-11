function filled = computeDate(filled, date)
    start_time = datetime(date,'InputFormat','uuuu-MM-dd_HH-mm-ss');
    
    for i = 1 : size(filled,1)
       filled(i,1) = filled(i,1) - filled(1,1);
    end
    
    cast(filled(:,1),datetime);
    
    for i = 1 : size(filled,1)
       filled(i,1) = start_time + milliseconds(filled(i,1));
    end
end