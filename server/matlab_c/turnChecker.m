%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Takes in input the accx parameter that represents the frontal G
%   Evolution over time.
%   Return a nx7 matrix where each rows represents a sudden event
%   (acceleration/braking)
%    columns={starting sample, interval, directions, accx average, accx variance}
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function turns = turnChecker(accx, accy, giroz, turn_peaks_threshold)
      turn_lower_size = 15;
      noise_threshold = 0.01;
      turn_complete = 0;
      n_candidates = 0;
      turns = 0;
      
      %peaks search
      for i = 1 : size(accy,1)
        if(turn_complete == 0 && abs(accy(i)) > turn_peaks_threshold)
            n_candidates = n_candidates + 1;
            turn_complete = 1;
            
            if(giroz(i) > 0)
               direction = 1;
            else 
               direction = -1;
            end    
         end
         
        %turn interval computing
        if(turn_complete == 1 && ((accy(i) < 0 && direction == 1) || (((abs(accy(i)) < noise_threshold || accy(i) > 0 ) && direction == -1) ) || i == size(accy,1)))
            turn_complete = 0;
        end     
      end  
      
      if (~n_candidates == 0)
          turns = zeros(n_candidates, 2);
          turn_complete = 0;
          index = 1;
          
          for i = 1 : size(accy,1)
            if(turn_complete == 0 && abs(accy(i)) > turn_peaks_threshold)
                turns(index, 1) = i;
                turn_complete = 1;

                if(giroz(i) > 0)
                   direction = 1;
                else 
                   direction = -1;
                end 
             end

            % Turn interval computing
            if(turn_complete == 1 && ((accy(i) < 0 && direction == 1) || (((abs(accy(i)) < noise_threshold || accy(i) > 0 ) && direction == -1) ) || i == size(accy,1)))
                turns(index,3) = i - turns(index, 1);
                turns(index,2) = abs(mean(accx(turns(index, 1) : i)));
                turn_complete = 0;
                index = index + 1;
            end     
          end     

          % Filtering 
          turns = turns(turns(:,3) > turn_lower_size, :);
          if(isempty(turns))
              turns = 0;
          end
      end
end