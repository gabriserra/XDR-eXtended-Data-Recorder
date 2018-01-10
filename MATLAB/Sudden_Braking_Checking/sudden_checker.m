function [ output_args ] = sudden_checker( denoised )
    if(size(denoised,1) == 1)
        denoised = denoised';
    end
    
    length = size(denoised,1);
    j=1;
    for i=1:1:length-1
        if(abs(denoised(i,1)-denoised(i+1,1)) > 0.2)
        candidates(j,1) = i;
        if(denoised(i,1)-denoised(i+1,1) < 0)
            directions(j,1) = 1;
        else
            directions(j,1) = -1;
        end
        j=j+1;
        end
    end
    [directions candidates]
    plot(denoised)
    for i=1:1:size(candidates,1)
        
        j=candidates(i,1);
        if(directions(i,1) == 1)
            
            while (abs(denoised(j+1) - denoised(j)) < 10^-4 || denoised(j+1) >= denoised(j) )
                j = j+1;
            end
            interval(i,1) = j-candidates(i,1);
        
        else
            while ( denoised(j)- denoised(j+1) > 0.05 )
                j = j+1;
            end
            interval(i,1) = j-candidates(i,1);
        
        end
    end
    [candidates interval directions]    
    %adesso calcolarsi i g totali negli intervalli di tempo
   
end

