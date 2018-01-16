%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Takes in input the accx parameter that represents the frontal G
%   Evolution over time.
%   Return a nx4 matrix where each rows represents a sudden event
%   (acceleration/braking)
%    columns={starting sample,time interval (sample),acc intensity, acc/interval}
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [ data ] = sudden_checker(accx)    
      acc_threshold = 0.04;
      brake_threshold = -0.1;
      turning = 0;
      j=1;
      start =0;
      candidates=0;
      interval=0;
      directions=0;
      
      %checks for sudden candidates also computing associated directions
      for i=1:1:size(accx,1)
      
        if(turning == 0 && (accx(i,1) >  acc_threshold  || accx(i,1) <  brake_threshold) )
            start=i;
            candidates(j,1) = i;
            turning=1;
            
            if(accx(i,1) > 0)
               directions(j,1) = 1;
            else  
               directions(j,1) = -1;
            end
              j =j+1;
        end
         
        %computing sudden maneuvre's interval
        if(turning == 1 && ( ( (abs(accx(i,1)) <  acc_threshold  ||  accx(i,1)< 0) && directions(j-1,1) == 1) || (( abs(accx(i,1)) < -brake_threshold  && directions(j-1,1) == -1) ) || i == size(accx,1)))
            interval(j-1,1) = i-start;
            turning = 0;
        end
        
        
      end
        data=zeros(size(candidates,1),4);
      if(candidates ~= 0)
          %filtering
          [candidates interval]
          to_remove = find(interval < 15);
         % to_remove = find data
         candidates(to_remove) = [];
          interval(to_remove)= [];
          directions(to_remove)= [];
          data=zeros(size(candidates,1),4);
    
          %filling output matrix
          for i=1:1:size(candidates,1)
            data(i,1) = candidates(i,1);
            data(i,2) = interval(i,1);
            data(i,3) = directions(i,1);
            data(i,4) = mean( accx(candidates(i,1):candidates(i,1)+interval(i,1),1 ));
          end
          
%               to_remove = find(data(:,4) >  brake_intensity_threshold & data(:,3) == -1 )
%               data(to_remove,:)=[];
      end  
end