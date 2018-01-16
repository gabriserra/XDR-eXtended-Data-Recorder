%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Takes in input the accx parameter that represents the frontal G
%   Evolution over time.
%   Return a nx2 matrix where each rows represents a sudden event
%   (acceleration/braking)
%    columns = {start time, intensity}
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [acc, brake] = accBrakeChecker(accx, acc_threshold, brake_threshold)  
    n_candidates = 0;
    acc_brake_complete = 0;
    acc_brake_lower_size = 15;
    acc = 0;
    brake = 0;
    acc_brake = 0;
    
    % Computing number of candidates
    for i = 1 : size(accx,1)
        if (acc_brake_complete == 0 && (accx(i) >  acc_threshold  || accx(i) <  brake_threshold))
            n_candidates = n_candidates + 1;
            acc_brake_complete = 1;
            if(accx(i) > 0)
                    direction = 1;
                else  
                    direction = -1;
            end
        end
        
        if(acc_brake_complete == 1 && (((abs(accx(i)) < acc_threshold || accx(i) < 0) && direction == 1) || ((abs(accx(i)) < -brake_threshold  && direction == -1)) || i == size(accx,1)))
            acc_brake_complete = 0;
        end
    end
    
    if(n_candidates ~= 0)
        acc_brake = zeros(n_candidates, 4);
        index = 1;
        acc_brake_complete = 0;
        
        % Checks for sudden candidates also computing associated directions
        for i = 1 : size(accx,1)
            if (acc_brake_complete == 0 && (accx(i) >  acc_threshold  || accx(i) <  brake_threshold))
                acc_brake(index,1) = i;
                acc_brake_complete = 1;
                
                if(accx(i) > 0)
                    acc_brake(index,4) = 1;
                else  
                    acc_brake(index,4) = -1;
                end
            end

            % Computing sudden maneuvre's interval
            if(acc_brake_complete == 1 && (((abs(accx(i)) < acc_threshold || accx(i) < 0) && acc_brake(index,4) == 1) || ((abs(accx(i)) < -brake_threshold  && acc_brake(index,4) == -1)) || i == size(accx,1)))
                acc_brake(index,3) = i - acc_brake(index,1);
                acc_brake(index,2) = mean(accx(acc_brake(index,1) : i));
                acc_brake_complete = 0;
                index = index+1;
            end
        end
        
        acc_brake = acc_brake(acc_brake(:,3) >= acc_brake_lower_size, :);
        acc = acc_brake(acc_brake(:,4) > 0, 1:3);
        brake = acc_brake(acc_brake(:,4) < 0, 1:3);
        if(isempty(acc))
              acc = 0;
        end
        if(isempty(brake))
              brake = 0;
        end
    end
end