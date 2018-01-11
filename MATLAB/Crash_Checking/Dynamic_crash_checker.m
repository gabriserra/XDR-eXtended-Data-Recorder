function [crash] = Dynamic_crash_checker(accx)
    peaks = find(accx < -0.3);
    crash=0;
    found=0;
    j=1;
    for i=1:1:size(peaks,1)-1
        if(found == 0)
            crash(j,1) = peaks(i,1);
            j=j+1;
            found = 1;
        end
        
        if(found == 1 && abs(crash(j-1,1)-peaks(i,1)) > 10)
            found = 0;
            i = i-1;
        end
    end

end



