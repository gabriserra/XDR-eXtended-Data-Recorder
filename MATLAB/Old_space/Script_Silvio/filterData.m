function filtered = filterData(unfiltered)
    filtered = zeros(size(unfiltered,1), size(unfiltered,2));
    alpha = 0.5;
    beta = 0.3;
    
    filtered(1,:) = unfiltered(1,:);
    
    filtered(2,1) = unfiltered(2,1);
    filtered(2,2) = unfiltered(2,2);
    for j = 3 : 5
        filtered(2,j) = (1 - beta) * unfiltered(2,j) + (1 - alpha - beta) * unfiltered(2,j);
    end
    
    for i = 3 : size(unfiltered,1)
        filtered(i,1) = unfiltered(i,1);
        filtered(i,2) = unfiltered(i,2);
        for j = 3 : 5
            filtered(i,j) = alpha * unfiltered(i,j) + beta * unfiltered(i-1,j) + (1 - alpha - beta) * unfiltered(i-2,j);
        end
    end
end

