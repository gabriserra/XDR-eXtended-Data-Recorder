%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Takes in input the accx parameter that represents the frontal G
%   Evolution over time.
%   Return a nx4 matrix where each rows represents a static crash
%   columns={time, interval (sample),acc intensity, acc/interval,starting sample}
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function crash = staticCrashChecker(accx, static_lower)
    crash = 0;
    static_lower_intensity = 50;
    static_threshold = 0.1;
    min_distance = 10;
    static_upper_size = 10;
    
    %find all peaks
    peaks = find(abs(accx) > static_lower);

    i = 1;
    while(i <= size(peaks,1) && ~isempty(peaks))
        if(abs(accx(peaks(i) - 2)) > static_threshold || abs(accx(peaks(i) - 3)) > static_threshold || abs(accx(peaks(i) - 4)) > static_threshold || abs(accx(peaks(i) - 5)) > static_threshold)
            %removerows(peaks, i);
            peaks(i) = [];
        elseif(i > 1 && peaks(i) - peaks(i-1) < min_distance)
            %removerows(peaks, i);
            peaks(i) = [];
        else
            i = i + 1;
        end
    end

    % Directions contains sign of peaks, crash is the output
    if(~isempty(peaks))
        crash = zeros(size(peaks,1), 4);

        crash(:,1) = peaks;

        % for each peaks compute intensity and time interval
        for i = 1 : size(peaks)                                                 
            if(accx(peaks(i)) > 0)
                ends = find(accx(peaks(i) : size(accx,1)) < 0);
            else
                ends = find(accx(peaks(i) : size(accx,1)) > 0);
            end
            crash(i,4) = ends(1) - 1;                                     
            crash(i,2) = accx(peaks(i)) - accx(peaks(i) + crash(i,4));              
            crash(i,3) = crash(i,2) / crash(i,4) * 100;  
            crash(i,2) = accx(crash(i,1));
        end

        %filtering
        crash = crash(crash(:,4) <= static_upper_size, :);
        crash = crash(abs(crash(:,3)) >= static_lower_intensity, :);
        crash = crash(:,1:2);
        if(isempty(crash))
            crash = 0;
        end
    end
end

