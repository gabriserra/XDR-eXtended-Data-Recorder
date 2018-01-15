function timestamp = computeDate(filled, date)
    start_time = datetime(date,'InputFormat','uuuu-MM-dd_HH-mm-ss');
    timestamp = NaT(size(filled,1),1,'Format','uuuu-MM-dd_HH-mm-ss.SSSSSS');
    
    filled(:,1) = filled(:,1) - filled(1,1);
    
    for i = 1 : size(filled,1)
       timestamp(i,:) = start_time + milliseconds(filled(i,1));
    end
end