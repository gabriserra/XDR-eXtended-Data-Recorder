function [ brakings ] = Static_crash_checker(accx)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Takes in input the accx parameter that represents the frontal G
%   Evolution over time.
%   Return a nx4 matrix where each rows represents a static crash
%   columns={time interval (sample),acc intensity, acc/interval,starting sample}
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    %make sure that the input parameter has the right size
    if(size(accx,1) == 1)
        accx=accx';
    end
    
    %find all peaks
    peaks = find(abs(accx) > 0.5)   ;                 
    j=1;
    i=1;
    
    %find peaks' starting point, deleting adjacent peaks
    while(i< size(peaks,1)-1)   
        selected = peaks(i,1);
         i=i+1;
        to_remove = find( peaks (find ( peaks(i:size(peaks,1),1) -selected < 10)))+ (i-1);
        peaks(to_remove,:) = [];       
    end
    
    %directions contains sign of peaks, brakings is the output
    directions= zeros(size(peaks,1),1);
    brakings=zeros(size(peaks,1),4);
    
    for i=1:1:size(peaks,1)
        if(accx(peaks(i,1),1) > 0)
            directions(i,1) = 1;
        else
            directions(i,1) =- 1;
        end
    end
 
    brakings(:,4) = peaks;
    
    %%for each peaks compute intensity and time interval
    for i=1:1:size(peaks,1)                                                 
        if(directions(i,1) > 0)
            ends=find(accx(peaks(i,1):size(accx,1)) < 0);
        else
            ends=find(accx(peaks(i,1):size(accx,1)) > 0);
        end
        brakings(i,1) = ends(1,1)-1;                                       
        brakings(i,2) = accx(peaks(i,1)) - accx(brakings(i,4)+ brakings(i,1),1);              
        brakings(i,3) = brakings(i,2)/brakings(i,1)*100;                        
    end

end
