%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Takes in input the accx parameter that represents the frontal G
%   Evolution over time.
%   Return a nx2 matrix where each rows represents a static crash
%   columns={starting sample, time interval}
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [crash] = Dynamic_crash_checker(accx)
    dynamic_upper = -0.1;
    dynamic_lower = -1.5;
    dynamic_ending = 0.08;
    dynamic_upper_size = 15;
    dynamic_lower_size = 3;
    crash=0;
    found=0;
    j=1;
    i=1;
    
    %find peaks
    peaks = find(accx < dynamic_upper & accx > dynamic_lower );
   
    %filter near pairs of peaks
    while (i < size(peaks,1)-1)
        
        if(found == 0)
            crash(j,1) = peaks(i,1);
            j=j+1;
            found = 1;
        end
        
        if(found == 1 && abs(crash(j-1,1)-peaks(i,1)) > 25)
            found = 0;
            i = i-1;
        end
        i=i+1;
    end

    %search dynamic crash ending
    if(crash ~= 0)
        
        for i=1:1:size(crash,1)  
            ends=find(abs(accx(crash(i,1):size(accx,1))) < dynamic_ending);
            crash(i,2) = ends(1,1);
            crash(i,3) = max(abs(accx(crash(i,1):crash(i,1)+crash(i,2))));
        end
        
        %remove outliers
        to_remove = find(crash(:,2)> dynamic_upper_size);
        crash(to_remove,:)=[];
        to_remove = find(abs(crash(:,2)) < dynamic_lower_size)  ;
        crash(to_remove,:)=[];
    else
         crash=0;
    end
end
    



