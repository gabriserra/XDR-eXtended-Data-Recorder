
function filled = filler(unfilled)
    
    length = size(unfilled,1);
%     if(size(unfilled,1) > 1)
%         unfilled = unfilled';
%     end
    
    max = unfilled(size(unfilled,1),1)+1;
    filled = -ones(max,size(unfilled,2))*10;
    reference = [1:1:max]-1';
    filled(:,1) = reference; 
    
    for i=1:1:max
        
        index = find(unfilled(:,1) == i-1);
        if(~isempty(index))
             for z=2:1:size(filled,2)               
                filled(i,z) = unfilled(index,z); 
             end
        end
        
    end
    for i=1:1:max
        
        if(filled(i,2) == -10)
           
           j = i;
           while(filled(j,2) == -10)
                j = j+1;
           end
              for z=2:1:size(filled,2)   
                index1 = find(unfilled(:,1)== i-2) ;
                step =  (unfilled(index1,z) - unfilled(index1+1,z))/(j-i+1);
                range = 1:1:(j-i);
                filled((i):(j-1),z) = [unfilled(index1,z) - range*step]'; 
              end
        end
    end  
end

