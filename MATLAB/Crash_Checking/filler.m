function filled = filler(unfilled)
    size(unfilled,1) 
    if(size(unfilled,1) == 2)
        unfilled = unfilled';
    end
    
    length = unfilled(size(unfilled,1),1)
    filled = zeros(length,1);
    reference = [1:1:length]';
    initial_missing=-1;
    for i=1:1:length
        if(i ~= unfilled(i,1)+1 )
           if(initial_missing == -1)
                initial_missing = i;
           end
        else
            if(initial_missing ~= -1)
                filled(initial_missing:i,1) = create_intermediaries(unfilled( initial_missing-1, 1), i-initial_missing, abs( ( unfilled( initial_missing-1, 1) - unfilled(i+1, 1) ) ) )
            else
                filled(i,1) = unfilled(i,2); 
            end
            
        end
        
        
    end
    
    [reference filled]
    
 
    
end


%%hint 

%creare un vettore da 1 a maxsequencevalue
%copiare i (sequence-1) nel vettore create
%gli elementi rimasti a 0 vanno ripienati
%prendere estremi e lanciare la create intermediaries