%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Takes in input the accx parameter that represents the frontal G
%   Evolution over time.
%   Return a nx7 matrix where each rows represents a sudden event
%   (acceleration/braking)
%    columns={starting sample, interval, directions, accx average, accx variance}
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [data]=Turn_Checker(accx,accy,giroz)
      turn_peaks_threshold = 0.25;
      turn_end_threshold = 1;
      turn_lower_size = 15;
      data=0;
      
      %check sizes
      if(size(accx,1) == 1)
        accx=accx';
      end
      if(size(accy,1) == 1)
        accx=accx';
      end
      if(size(giroz,1) == 1)
        accx=accx';
      end
      
      turning = 0;
      j=1;
      start =0;
      candidates=0;
      
      %peaks search
      for i=1:1:size(accy,1)
      
        if(turning == 0 && abs(accy(i,1)) > turn_peaks_threshold)
            start=i;
            candidates(j,1) = i;
            turning=1;
            
            if(giroz(i,1) > 0)
               directions(j,1) = 1;
            else 
               directions(j,1) = -1;
            end    
                j =j+1; 
         end
         
        %turn interval computing
        if(turning == 1 && ( (accy(i,1) < 0 && directions(j-1,1) == 1) || (( (abs(accy(i,1)) < 0.1 || accy(i,1) > 0 ) && directions(j-1,1) == -1) ) || i == size(accy,1)))
            interval(j-1,1) = i-start;
            turning = 0;
        end     
      end     
      
      if(candidates ~= 0 )
          
          %filtering 
          to_remove = find(interval < turn_lower_size);
          candidates(to_remove) = [];
          interval(to_remove)= [];
          directions(to_remove)= [];
          data=zeros(size(candidates,1),7);
          
          %filling output matrix
          if(~isempty(candidates))
              for i=1:1:size(candidates,1)
                data(i,1) = candidates(i,1);
                data(i,2) = interval(i,1);
                data(i,3) = directions(i,1);
                data(i,4) = mean( accx(candidates(i,1):candidates(i,1)+interval(i,1),1 ));
                data(i,5) = sum((accx(candidates(i,1):candidates(i,1)+interval(i,1),1) - data(i,4)).^2 );
                data(i,5) = data(i,5)/interval(i,1);
                data(i,6) = mean(iomega(accx(candidates(i,1):candidates(i,1)+interval(i,1),1),1/50,3,2));
                data(i,7) = sum((iomega(accx(candidates(i,1):candidates(i,1)+interval(i,1),1),1/50,3,2) - data(i,6)).^2 );
                data(i,7) = data(i,7)/interval(i,1);
              end  
          end
      end
end