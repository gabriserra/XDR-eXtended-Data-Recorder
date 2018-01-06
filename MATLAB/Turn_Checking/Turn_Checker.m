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
    
      turns = find(giroz > 10);
      turns(1,1)
      i=1;
      j=1;
      next_index=turns(1,1);

     while (~isempty(next_index))
          end_turn = find(giroz(next_index:size(giroz,1),1)< 0) -1;
          end_turn =end_turn(1,1);
          next = next_index+end_turn(1,1)                                     %indice fine curva
               
          data(j,1) = next_index;                                             %starting point
          data(j,2) = end_turn(1,1);                                          %interval
          data(j,3) = mean(abs(accx(next_index:next,1)));       
          data(j,4) = mean(abs(accy(next_index:next,1)));       
          data(j,5) = var(abs(accy(next_index:next,1)));  
          
          next_index = find(turns > next);                                    %prossimo punto iniziale
       
          if(~isempty(next_index))
            next_index = next_index(1,1)
            next_index = turns(next_index,1);                                               %punto di partenza nuovo        
          end       
          j=j+1;

     end


end