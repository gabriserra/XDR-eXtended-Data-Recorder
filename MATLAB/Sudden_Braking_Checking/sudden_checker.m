function [ data ] = sudden_checker(accx)    
      turning = 0;
      j=1;
      start =0;
      candidates=0;
      interval=0;
      directions=0;
      for i=1:1:size(accx,1)
      
        if(turning == 0 && (accx(i,1) > 0.4 || accx(i,1) < -0.1) )
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
         
         %fare controllo non proprio per il segno ma per la vicinanza allo
         %0 in assoluto (10^-4)
        if(turning == 1 && ( ( (abs(accx(i,1)) < 10^-2 ||  accx(i,1)< 0) && directions(j-1,1) == 1) || ((  abs(accx(i,1)) < 10^-2  && directions(j-1,1) == -1) ) || i == size(accx,1)))
            interval(j-1,1) = i-start;
            turning = 0;
        end
        
        
      end
 
      [candidates interval];
      to_remove = find(interval < 2);
      candidates(to_remove) = [];
      interval(to_remove)= [];
      directions(to_remove)= [];
      data=zeros(size(candidates,1),4);
    
      for i=1:1:size(candidates,1)
          
        data(i,1) = candidates(i,1);
        data(i,2) = interval(i,1);
        data(i,3) = directions(i,1);
        data(i,4) = mean( accx(candidates(i,1):candidates(i,1)+interval(i,1),1 ));
     
      end
        
end