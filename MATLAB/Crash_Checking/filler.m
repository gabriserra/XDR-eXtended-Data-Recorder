function filled = filler(unfilled)
    
    length = size(unfilled,1);
%     if(size(unfilled,1) > 1)
%         unfilled = unfilled';
%     end
    
    max = unfilled(size(unfilled,1),1)+1;
    filled = -ones(max,size(unfilled,1),2)*10;
    reference = [1:1:max]-1';
    filled(:,1) = reference; 
    
    for i=1:1:max
        
        index = find(unfilled(:,1) == i-1);
        if(~isempty(index))
            filled(i,2) = unfilled(index,2); 
        end
        
    end
 
    for i=1:1:max
        
        if(filled(i,2) == -10)
           
           j = i;
           while(filled(j,2) == -10)
                j = j+1;
           end
           size(unfilled,2)
              for z=2:1:size(unfilled,2)
                 
              filled((i):(j-1),z) = create_intermediaries(unfilled(i-1,z),j-i,abs( unfilled(i-1,z) - unfilled(i,z)))';
              end
        end
    end  
end