function filtered = filterData(unfiltered)
    alpha = 0.5;
    filtered = unfiltered;
    
    for k = 1 : 100
        for i = 2 : size(filtered,1)
            filtered(i) = alpha * filtered(i) + (1 - alpha) * filtered(i-1);
        end
    end
end

