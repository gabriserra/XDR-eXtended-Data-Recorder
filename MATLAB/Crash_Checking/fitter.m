function fitted = fitter(sig )
%     if(size(sig,1) == 1)
%         sig = sig';
%     end
    
    sig_length = size(sig,1);
    fitted_length = (sig_length-1)+sig_length;
    fitted = zeros(fitted_length,size(sig,2));
    j=1;
    for i=1:1:fitted_length
        if(mod(i,2) ~= 0)
            fitted(i,2:size(fitted,2)) =sig(j,2:size(fitted,2));
            fitted(i,1) = i-1;
            j=j+1;
        end
    end

    for i=1:1:fitted_length-1
         if(fitted(i,1) == 0)
             i
            step = ( fitted(i,:) - fitted(i+1,:) )/2;
            fitted(i,:) = fitted(i,:)-step;
         end
    end
        
    
end