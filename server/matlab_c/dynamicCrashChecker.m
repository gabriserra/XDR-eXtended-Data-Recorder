%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Takes in input the accx parameter that represents the frontal G
%   Evolution over time.
%   Return a nx2 matrix where each rows represents a static crash
%   columns={starting sample, time interval}
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function crash = dynamicCrashChecker(accx, dynamic_upper, dynamic_lower)  
    crash = 0;
    % Intervallo di tempo
    dynamic_upper_size = 50;
    dynamic_lower_size = 3;
    
    %find peaks
    peaks = find(accx < dynamic_upper & accx > dynamic_lower);
    
    if(peaks ~= 0)
        crash = zeros(size(peaks,1), 3);

        % search dynamic crash ending
        for i = 1 : size(peaks, 1)  
            ends = find(accx(peaks(i) : size(accx)) > 0);
            crash(i,1) = peaks(i);
            
            if(isempty(ends))
                crash(i,3) = size(accx,1) - crash(i,1);
            else
                crash(i,3) = ends(1);
            end
            crash(i,2) = max(abs(accx(crash(i,1) : crash(i,1) + crash(i,3))));
        end

        crash = crash(crash(:,3) <= dynamic_upper_size, :);
        crash = crash(crash(:,3) >= dynamic_lower_size, :);
        
        i = 1;
        %filter near pairs of peaks
        while i < size(crash, 1)
            reference = crash(i,1) + crash(i,3);
            
            if(i < size(crash,1))
                crash(i + find(crash(i+1:size(crash, 1), 1) < reference ),:)=[];
            end
            i=i+1;
        end
        crash = crash(:,1:2);
        if(isempty(crash))
            crash = 0;
        end
    end
end