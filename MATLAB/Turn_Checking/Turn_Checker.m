%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Prende come input le tre grandezze ricevute, per testarla:
%           1) Caricare la workspace turns.mat
%           2) Lanciare prepare (denoise+filler)
%           3) eseguire Turn_Checker(var(:,2),var(:,3),var(:,4));
%
% L'output restituito è:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [data]=Turn_Checker(accx,accy,giroz)
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
      for i=1:1:size(giroz,1)
      
        if(turning == 0 && abs(giroz(i,1)) > 4)
            start=i;
            if(giroz(i,1) > 0)
               directions(j,1) = 1;
            else
                
               directions(j,1) = -1;
            end
                candidates(j,1) = i;
                j =j+1;
                turning=1;
        end
         
         if(j>1 && candidates(j-1,1) == 1859)
             turning
             giroz(i,1)
             directions
         end
        if(turning == 1 && ( (giroz(i,1) < 0 && directions(j-1,1) == 1) || ((giroz(i,1) > 0 && directions(j-1,1) == -1) )))
            interval(j-1,1) = i-start;
            turning = 0;
        end
        
        
      end
 
      [candidates interval]
      for i=1:1:size(candidates,1)
        %qui è necessario considerare ogni intervallo in cui si curve e scegliere se:
        %       1) basarsi su accx 
        %       2) basarsi su la velocità ottenuta con iomega (attendibile?)
      end
      
     
end