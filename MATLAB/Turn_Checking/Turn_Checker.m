%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Prende come input le tre grandezze ricevute, per testarla:
%           1) Caricare la workspace turns.mat
%           2) Lanciare prepare (denoise+filler)
%           3) eseguire Turn_Checker(var(:,2),var(:,3),var(:,4));
%
% L'output restituito è:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [data]=Turn_Checker(accx,accy,giroz)
      data=0;
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
      
        if(turning == 0 && abs(giroz(i,1)) > 100)
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
         
         %fare controllo non proprio per il segno ma per la vicinanza allo
         %0 in assoluto (10^-4)
        if(turning == 1 && ( (giroz(i,1) < 0 && directions(j-1,1) == 1) || (( (abs(giroz(i,1)) < 4 || giroz(i,1) > 0.5 ) && directions(j-1,1) == -1) ) || i == size(giroz,1)))
            interval(j-1,1) = i-start;
            turning = 0;
        end
        
        
      end
      if(candidates ~= 0)
          [candidates interval];
          to_remove = find(interval < 20);
          candidates(to_remove) = [];
          interval(to_remove)= [];
          directions(to_remove)= [];
          [candidates interval directions];
          data=zeros(size(candidates,1),7);
      
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