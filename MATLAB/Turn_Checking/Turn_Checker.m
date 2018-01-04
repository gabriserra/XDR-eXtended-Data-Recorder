function [a]=Turn_Checker(accx,accy,giroz)
      if(size(accx,1) == 1)
        accx=accx';
      end
      if(size(accy,1) == 1)
        accx=accx';
      end
      if(size(giroz,1) == 1)
        accx=accx';
      end
    
      turns = find(abs(giroz) > 10)
      i=1;
      j=1;
      next=0;
     while (j<2)
          end_turn = find(giroz(turns(i,1):size(giroz,1),1)< 0) -1;
          next = turns(i,1)+end_turn(1,1);
          %ripartire dal next alla prossima iterazioni (cercare il valore in turns subito maggiore di end_turn+turns)
          data(j,1) = turns(i,1);                                             %starting point
          data(j,2) = end_turn(1,1)      ;                                     %time interval   
        %  data(j,3) = mean(accx(turns(i,1): end_turn(1,1)-turns(i,1)));
        %  data(j,4) = mean(accy(turns(i,1): end_turn(1,1)-turns(i,1)));
        %  data(j,5) = var(accy(turns(i,1): end_turn(1,1)-turns(i,1)));
       %  turns = removerows(turns,'ind',index)
        j=j+1;
        
        %rimuovi tutte gli elementi in turns compresi tra turns(i,1) e il
        %risultato di find(0)
     end


end