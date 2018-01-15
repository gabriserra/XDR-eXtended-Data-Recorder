function filled = filler(unfilled)
    n_elements = size(unfilled,1);
    
    filled = zeros(unfilled(n_elements,2) - unfilled(1,2) + 1, size(unfilled, 2));
    
    index = 1;
    filled(index,:) = unfilled(index,:);
    filled(index,2) = index;
    index = index + 1;
    
    for i = index : size(unfilled,1)
        diff = unfilled(i,2) - unfilled(i-1,2);
        if(diff == 1)
            filled(index,:) = unfilled(i,:);
            filled(index,2) = index;
            index = index + 1;
        else
            for k = 1 : diff - 1
                for j = 1 : 5
                    if j~= 2
                        delta = (unfilled(i,j) - unfilled(i-1,j)) / diff;
                        filled(index,j) = unfilled(i-1,j) + delta * k;
                    end
                end
                filled(index,2) = index;
                index = index + 1;
            end
            filled(index,:) = unfilled(i,:);
            filled(index,2) = index;
            index = index + 1;
        end
    end
end

