function [intermediaries] = create_Intermediaries(start,interval,delta)
    step = delta/(interval+1);
    range = 1:1:interval;
    intermediaries = start -range*step; 
end

