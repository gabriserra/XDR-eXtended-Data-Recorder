%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Takes in input the accx parameter that represents the frontal G
%   Evolution over time.
%   Return a nx2 matrix where each rows represents a static crash
%   columns={starting sample, time interval}
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [crash] = Dynamic_crash_checker(accx)
    dynamic_upper = -0.05;
    dynamic_lower = -0.5;
    dynamic_upper_size = 50;
    dynamic_lower_size = 3;
    crash=0;
    j=1;
    i=1;
    
    %find peaks
    peaks = find(accx < dynamic_upper & accx > dynamic_lower );
   
    %filter near pairs of peaks   

    %search dynamic crash ending
    if(peaks ~= 0)
        
        for i=1:1:size(peaks,1)  
            ends=find( accx(peaks(i,1):size(accx,1))>0 );   
           
            crash(i,1) = peaks(i,1);
            if(isempty(ends))
                crash(i,2) = size(accx,1)-crash(i,1);
            else
                crash(i,2) = ends(1,1);
            end
  
            crash(i,3) = max(abs(accx(crash(i,1):crash(i,1)+crash(i,2))));
        end
        
        %remove outliers

        to_remove = find(crash(:,2) > dynamic_upper_size);
        crash(to_remove,:)=[];
        to_remove = find(abs(crash(:,2)) < dynamic_lower_size)  ;
        crash(to_remove,:)=[];
        i=1;
        j=1;
        crash

    while( i < size(crash,1))
        reference= crash(i,1)+crash(i,2);
        
        if(i < size(crash,1))
          crash(i+find( crash(i+1:size(crash,1),1) < reference ),:)=[];
        end 
        i=i+1;
       end
       
    else
         crash=0;
    end
end
    



